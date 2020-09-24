/*
    framegraphutils.cpp

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Paul Lemire <paul.lemire@kdab.com>

    Licensees holding valid proprietary KDAB Kuesa licenses may use this file in
    accordance with the Kuesa Enterprise License Agreement provided with the Software in the
    LICENSE.KUESA.ENTERPRISE file.

    Contact info@kdab.com if any conditions of this licensing are not clear to you.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "framegraphutils_p.h"
#include <private/kuesa_p.h>

#include <Qt3DRender/qrendertarget.h>
#include <Qt3DRender/qtexture.h>

#include <QOffscreenSurface>
#include <QOpenGLContext>

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
#include <private/qrhi_p.h>
#endif

QT_BEGIN_NAMESPACE

namespace Kuesa {

FrameGraphUtils::RenderingFeatures FrameGraphUtils::m_renderingFeatures = {};

/*!
 * \internal
 *
 * Helper function to create a QRenderTarget with the correct texture formats
 * and sizes.
 */
FrameGraphUtils::RenderingFeatures FrameGraphUtils::checkRenderingFeatures()
{
    static bool wasInitialized = false;
    if (wasInitialized)
        return FrameGraphUtils::m_renderingFeatures;

    QOffscreenSurface offscreen;
    QOpenGLContext ctx;
    FrameGraphUtils::RenderingFeatures features;

    if (qgetenv("QT3D_RENDERER") != QByteArray("rhi")) {
        offscreen.setFormat(QSurfaceFormat::defaultFormat());
        offscreen.create();
        Q_ASSERT_X(offscreen.isValid(), Q_FUNC_INFO, "Unable to create offscreen surface to gather capabilities");

        ctx.setFormat(QSurfaceFormat::defaultFormat());
        if (ctx.create()) {
            ctx.makeCurrent(&offscreen);
            const QSurfaceFormat format = ctx.format();
            // Since ES 3.0 or GL 3.0
            features.hasHalfFloatTexture = (format.majorVersion() >= 3 || ctx.hasExtension(QByteArray("GL_OES_texture_half_float")));
            // Since GL 3.0 or ES 3.2 or extension
            features.hasHalfFloatRenderable = (ctx.isOpenGLES() ? (format.majorVersion() == 3 && format.minorVersion() >= 2)
                                                                : format.majorVersion() >= 3) ||
                    ctx.hasExtension(QByteArray("GL_EXT_color_buffer_half_float"));
            // Since ES 3.1, GL 3.0 or extension
            features.hasMultisampledTexture = (ctx.isOpenGLES() ? (format.majorVersion() == 3 && format.minorVersion() >= 1)
                                                                : (format.majorVersion() >= 3)) ||
                    ctx.hasExtension(QByteArray("ARB_texture_multisample"));
#if QT_VERSION <= QT_VERSION_CHECK(5, 12, 5) || (QT_VERSION >= QT_VERSION_CHECK(5, 13, 0) && QT_VERSION <= QT_VERSION_CHECK(5, 13, 1))
            // Blitting bug in Qt3D prevents correct depth blitting with multisampled FBO
            // Fixed for 5.12.6/5.13/2 with https://codereview.qt-project.org/c/qt/qt3d/+/276774
#else
            // Since ES 3.1, GL 3.0 or extension
            // TO DO: Find how to support that on ES
            features.hasMultisampledFBO = (ctx.isOpenGLES() ? (format.majorVersion() >= 3 && format.minorVersion() >= 1)
                                                            : format.majorVersion() >= 3);
#endif
            const bool forceMultisampledFBO = qgetenv("KUESA_FORCE_MULTISAMPLING").length() > 0;
            features.hasMultisampledFBO |= forceMultisampledFBO;

            ctx.doneCurrent();
        }
    } else {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        // TO DO: Update QRenderCapabilities and use that instead
        features.hasHalfFloatTexture = true;
        features.hasHalfFloatRenderable = true;
        features.hasMultisampledTexture = true;
        features.hasMultisampledFBO = true;
#endif
    }

    wasInitialized = true;
    FrameGraphUtils::m_renderingFeatures = features;

    qCDebug(kuesa) << "Rendering Features:\n"
                   << "hasHalfFloatTexture" << features.hasHalfFloatTexture << "\n"
                   << "hasHalfFloatRenderable" << features.hasHalfFloatRenderable << "\n"
                   << "hasMultisampledTexture" << features.hasMultisampledTexture << "\n"
                   << "hasMultisampledFBO" << features.hasMultisampledFBO;

    return features;
}

bool FrameGraphUtils::hasHalfFloatRenderable()
{
    const FrameGraphUtils::RenderingFeatures features = FrameGraphUtils::checkRenderingFeatures();
    return features.hasHalfFloatRenderable;
}

Qt3DRender::QRenderTarget *FrameGraphUtils::createRenderTarget(RenderTargetFlags flags,
                                                               Qt3DCore::QNode *owner,
                                                               const QSize surfaceSize,
                                                               int samples)
{
    auto renderTarget = new Qt3DRender::QRenderTarget(owner);
    Qt3DRender::QAbstractTexture *colorTexture = nullptr;
    if (flags & RenderTargetFlag::Multisampled) {
        colorTexture = new Qt3DRender::QTexture2DMultisample;
        colorTexture->setSamples(samples);
    } else {
        colorTexture = new Qt3DRender::QTexture2D;
    }
    // We need to use 16 based format as our content is HDR linear
    // which we will eventually exposure correct, tone map to LDR and
    // gamma correct
    // This requires support for extension OES_texture_half_float on ES2 platforms
    colorTexture->setFormat((flags & RenderTargetFlag::HalfFloatAttachments)
                            ? Qt3DRender::QAbstractTexture::RGBA16F
                            : Qt3DRender::QAbstractTexture::RGBA8_UNorm);
    colorTexture->setGenerateMipMaps(false);
    colorTexture->setSize(surfaceSize.width(), surfaceSize.height());
    auto colorOutput = new Qt3DRender::QRenderTargetOutput;

    colorOutput->setAttachmentPoint(Qt3DRender::QRenderTargetOutput::Color0);
    colorOutput->setTexture(colorTexture);
    renderTarget->addOutput(colorOutput);

    // Three options:
    // Depth is requested
    // Stencil is requested
    // Depth and stencil is requested

    const auto depthStencilFlags = flags & (RenderTargetFlag::IncludeDepth | RenderTargetFlag::IncludeStencil);
    if (depthStencilFlags) {
        Qt3DRender::QAbstractTexture::TextureFormat textureFormat = Qt3DRender::QAbstractTexture::NoFormat;
        Qt3DRender::QRenderTargetOutput::AttachmentPoint attachmentPoint = Qt3DRender::QRenderTargetOutput::Color0;
        if (depthStencilFlags == RenderTargetFlag::IncludeDepth) {
            textureFormat = Qt3DRender::QAbstractTexture::D24;
            attachmentPoint = Qt3DRender::QRenderTargetOutput::Depth;
        }
        if (depthStencilFlags == RenderTargetFlag::IncludeStencil) {
            textureFormat = Qt3DRender::QAbstractTexture::D24S8;
            attachmentPoint = Qt3DRender::QRenderTargetOutput::Stencil;
        }
        if (depthStencilFlags == (RenderTargetFlag::IncludeDepth | RenderTargetFlag::IncludeStencil)) {
            textureFormat = Qt3DRender::QAbstractTexture::D24S8;
            attachmentPoint = Qt3DRender::QRenderTargetOutput::DepthStencil;
        }

        Q_ASSERT(textureFormat != Qt3DRender::QAbstractTexture::NoFormat);
        Q_ASSERT(attachmentPoint != Qt3DRender::QRenderTargetOutput::Color0);

        Qt3DRender::QAbstractTexture *texture = nullptr;
        if (flags & RenderTargetFlag::Multisampled) {
            texture = new Qt3DRender::QTexture2DMultisample;
            texture->setSamples(samples);
        } else {
            texture = new Qt3DRender::QTexture2D;
        }
        texture->setSize(surfaceSize.width(), surfaceSize.height());
        texture->setGenerateMipMaps(false);
        texture->setFormat(textureFormat);
        auto depthStencilOutput = new Qt3DRender::QRenderTargetOutput;
        depthStencilOutput->setAttachmentPoint(attachmentPoint);
        depthStencilOutput->setTexture(texture);
        renderTarget->addOutput(depthStencilOutput);
    }

    return renderTarget;
}

bool FrameGraphUtils::renderTargetHasAttachmentOfType(const Qt3DRender::QRenderTarget *target,
                                                      const Qt3DRender::QRenderTargetOutput::AttachmentPoint attachmentType)
{
    if (!target)
        return false;
    const auto &outputs = target->outputs();
    for (const Qt3DRender::QRenderTargetOutput *output : outputs) {
        if (output->attachmentPoint() == attachmentType)
            return true;
    }
    return false;
}

/*!
 * \internal
 *
 * Helper function to retrieve the texture for the specified attachment point
 * in a QRenderTarget
 */
Qt3DRender::QAbstractTexture *FrameGraphUtils::findRenderTargetTexture(Qt3DRender::QRenderTarget *target,
                                                                       Qt3DRender::QRenderTargetOutput::AttachmentPoint attachmentPoint)
{
    auto outputs = target->outputs();
    auto attachment = std::find_if(outputs.begin(), outputs.end(), [attachmentPoint](Qt3DRender::QRenderTargetOutput *output) {
        return output->attachmentPoint() == attachmentPoint;
    });
    return attachment == outputs.end() ? nullptr : (*attachment)->texture();
}

} // Kuesa

QT_END_NAMESPACE
