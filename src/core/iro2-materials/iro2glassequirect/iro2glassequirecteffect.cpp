
/*
    iro2glassequirecteffect.cpp

    This file is part of Kuesa.

    Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Nicolas Guichard <nicolas.guichard@kdab.com>

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

#include "iro2glassequirecteffect.h"

#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QCullFace>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QShaderProgramBuilder>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DRender/QBlendEquation>
#include <Qt3DRender/QBlendEquationArguments>

QT_BEGIN_NAMESPACE

using namespace Qt3DRender;

namespace Kuesa {

class Iro2GlassEquiRectTechnique : public Qt3DRender::QTechnique
{
public:
    enum Version {
        GL3 = 0,
        ES3,
        ES2,
        RHI
    };

    explicit Iro2GlassEquiRectTechnique(Version version, Qt3DCore::QNode *parent = nullptr)
        : QTechnique(parent)
        , m_backFaceCulling(new QCullFace(this))
        , m_techniqueAllowFrustumCullingFilterKey(new QFilterKey(this))
    {
        struct ApiFilterInfo {
            int major;
            int minor;
            QGraphicsApiFilter::Api api;
            QGraphicsApiFilter::OpenGLProfile profile;
        };

        const ApiFilterInfo apiFilterInfos[] = {
            { 3, 1, QGraphicsApiFilter::OpenGL, QGraphicsApiFilter::CoreProfile },
            { 3, 0, QGraphicsApiFilter::OpenGLES, QGraphicsApiFilter::NoProfile },
            { 2, 0, QGraphicsApiFilter::OpenGLES, QGraphicsApiFilter::NoProfile },
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            { 1, 0, QGraphicsApiFilter::RHI, QGraphicsApiFilter::NoProfile },
#endif
        };

        graphicsApiFilter()->setApi(apiFilterInfos[version].api);
        graphicsApiFilter()->setProfile(apiFilterInfos[version].profile);
        graphicsApiFilter()->setMajorVersion(apiFilterInfos[version].major);
        graphicsApiFilter()->setMinorVersion(apiFilterInfos[version].minor);

        m_techniqueAllowFrustumCullingFilterKey->setName(QStringLiteral("allowCulling"));
        m_techniqueAllowFrustumCullingFilterKey->setValue(true);
        addFilterKey(m_techniqueAllowFrustumCullingFilterKey);

        auto filterKey = new QFilterKey(this);
        filterKey->setName(QStringLiteral("renderingStyle"));
        filterKey->setValue(QStringLiteral("forward"));
        addFilterKey(filterKey);
        {
            const QUrl vertexShaderGraph[] = {
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json"))
            };

            const QUrl fragmentShaderGraph[] = {
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2glassequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2glassequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2glassequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2glassequirect.frag.json"))
            };

            const QByteArray renderableVertexShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            const QByteArray renderableFragmentShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            const QByteArray renderableGeometryShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            auto renderShaderBuilder = new QShaderProgramBuilder(this);
            auto renderShader = new QShaderProgram(this);
            auto transparentRenderPass = new QRenderPass(this);

            // Use default vertex shader graph if no vertex shader code was specified
            if (renderableVertexShaderCode[version].isEmpty()) {
                renderShaderBuilder->setShaderProgram(renderShader);
                renderShaderBuilder->setVertexShaderGraph(vertexShaderGraph[version]);
            } else {
                renderShader->setVertexShaderCode(renderableVertexShaderCode[version]);
            }

            if (renderableFragmentShaderCode[version].isEmpty()) {
                renderShaderBuilder->setShaderProgram(renderShader);
                renderShaderBuilder->setFragmentShaderGraph(fragmentShaderGraph[version]);
            } else {
                renderShader->setFragmentShaderCode(renderableFragmentShaderCode[version]);
            }

            // Set geometry shader code if one was specified
            renderShader->setGeometryShaderCode(renderableGeometryShaderCode[version]);
            transparentRenderPass->setShaderProgram(renderShader);

            auto blendEquation = new Qt3DRender::QBlendEquation(this);
            blendEquation->setBlendFunction(Qt3DRender::QBlendEquation::Add);

            auto blendArguments = new Qt3DRender::QBlendEquationArguments(this);
            blendArguments->setSourceRgb(Qt3DRender::QBlendEquationArguments::Zero);
            blendArguments->setSourceAlpha(Qt3DRender::QBlendEquationArguments::One);
            blendArguments->setDestinationRgb(Qt3DRender::QBlendEquationArguments::SourceColor);
            blendArguments->setDestinationAlpha(Qt3DRender::QBlendEquationArguments::Zero);

            transparentRenderPass->addRenderState(m_backFaceCulling);
            transparentRenderPass->addRenderState(blendEquation);
            transparentRenderPass->addRenderState(blendArguments);

            auto transparentFilterKey = new Qt3DRender::QFilterKey(this);
            transparentFilterKey->setName(QStringLiteral("KuesaDrawStage"));
            transparentFilterKey->setValue(QStringLiteral("Transparent"));
            transparentRenderPass->addFilterKey(transparentFilterKey);

            auto transparentPassFilterKey = new Qt3DRender::QFilterKey(this);
            transparentPassFilterKey->setName(QStringLiteral("Pass"));
            transparentPassFilterKey->setValue(QStringLiteral("pass0"));
            transparentRenderPass->addFilterKey(transparentPassFilterKey);

            addRenderPass(transparentRenderPass);
        }
        {
            const QUrl vertexShaderGraph[] = {
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/metallicroughness.vert.json"))
            };

            const QUrl fragmentShaderGraph[] = {
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2reflectionequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2reflectionequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2reflectionequirect.frag.json")),
                QUrl(QStringLiteral("qrc:/kuesa/shaders/graphs/iro2reflectionequirect.frag.json"))
            };

            const QByteArray renderableVertexShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            const QByteArray renderableFragmentShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            const QByteArray renderableGeometryShaderCode[] = {
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()"),
                QByteArray(R"()")
            };

            auto renderShaderBuilder = new QShaderProgramBuilder(this);
            auto renderShader = new QShaderProgram(this);
            auto transparentRenderPass = new QRenderPass(this);

            // Use default vertex shader graph if no vertex shader code was specified
            if (renderableVertexShaderCode[version].isEmpty()) {
                renderShaderBuilder->setShaderProgram(renderShader);
                renderShaderBuilder->setVertexShaderGraph(vertexShaderGraph[version]);
            } else {
                renderShader->setVertexShaderCode(renderableVertexShaderCode[version]);
            }

            if (renderableFragmentShaderCode[version].isEmpty()) {
                renderShaderBuilder->setShaderProgram(renderShader);
                renderShaderBuilder->setFragmentShaderGraph(fragmentShaderGraph[version]);
            } else {
                renderShader->setFragmentShaderCode(renderableFragmentShaderCode[version]);
            }

            // Set geometry shader code if one was specified
            renderShader->setGeometryShaderCode(renderableGeometryShaderCode[version]);
            transparentRenderPass->setShaderProgram(renderShader);

            auto blendEquation = new Qt3DRender::QBlendEquation(this);
            blendEquation->setBlendFunction(Qt3DRender::QBlendEquation::Add);

            auto blendArguments = new Qt3DRender::QBlendEquationArguments(this);
            blendArguments->setSourceRgb(Qt3DRender::QBlendEquationArguments::One);
            blendArguments->setSourceAlpha(Qt3DRender::QBlendEquationArguments::Zero);
            blendArguments->setDestinationRgb(Qt3DRender::QBlendEquationArguments::One);
            blendArguments->setDestinationAlpha(Qt3DRender::QBlendEquationArguments::One);

            transparentRenderPass->addRenderState(m_backFaceCulling);
            transparentRenderPass->addRenderState(blendEquation);
            transparentRenderPass->addRenderState(blendArguments);

            auto transparentFilterKey = new Qt3DRender::QFilterKey(this);
            transparentFilterKey->setName(QStringLiteral("KuesaDrawStage"));
            transparentFilterKey->setValue(QStringLiteral("Transparent"));
            transparentRenderPass->addFilterKey(transparentFilterKey);

            auto transparentPassFilterKey = new Qt3DRender::QFilterKey(this);
            transparentPassFilterKey->setName(QStringLiteral("Pass"));
            transparentPassFilterKey->setValue(QStringLiteral("pass1"));
            transparentRenderPass->addFilterKey(transparentPassFilterKey);

            addRenderPass(transparentRenderPass);
        }
    }

    QStringList enabledLayers() const
    {
        const auto shaderBuilder = findChild<Qt3DRender::QShaderProgramBuilder *>();
        if (shaderBuilder != nullptr)
            return shaderBuilder->enabledLayers();
        return {};
    }

    void setEnabledLayers(const QStringList &layers)
    {
        const auto shaderBuilders = findChildren<Qt3DRender::QShaderProgramBuilder *>();
        for (auto shaderBuilder : shaderBuilders) {
            if (shaderBuilder != nullptr)
                shaderBuilder->setEnabledLayers(layers);
        }
    }

    void setOpaque(bool)
    {
    }

    void setCullingMode(QCullFace::CullingMode mode)
    {
        m_backFaceCulling->setMode(mode);
    }

    QCullFace::CullingMode cullingMode() const
    {
        return m_backFaceCulling->mode();
    }

    void setAllowCulling(bool allowCulling)
    {
        m_techniqueAllowFrustumCullingFilterKey->setValue(allowCulling);
    }

private:
    Qt3DRender::QCullFace *m_backFaceCulling;
    Qt3DRender::QFilterKey *m_techniqueAllowFrustumCullingFilterKey;
};


/*!
    \class Kuesa::Iro2GlassEquiRectEffect
    \inheaderfile Kuesa/Iro2GlassEquiRectEffect
    \inherits Qt3DRender::QEffect
    \inmodule Kuesa
    \since Kuesa 1.3

    \brief Kuesa::Iro2GlassEquiRectEffect is the effect for the Iro2GlassEquiRectMaterial class.
*/

/*!
    \qmltype Iro2GlassEquiRectEffect
    \instantiates Kuesa::Iro2GlassEquiRectEffect
    \inqmlmodule Kuesa
    \since Kuesa 1.3

    \brief Kuesa::Iro2GlassEquiRectEffect is the effect for the Iro2GlassEquiRectMaterial class.
*/


Iro2GlassEquiRectEffect::Iro2GlassEquiRectEffect(Qt3DCore::QNode *parent)
    : GLTF2MaterialEffect(parent)
{
    m_gl3Technique = new Iro2GlassEquiRectTechnique(Iro2GlassEquiRectTechnique::GL3, this);
    m_es3Technique = new Iro2GlassEquiRectTechnique(Iro2GlassEquiRectTechnique::ES3, this);
    m_es2Technique = new Iro2GlassEquiRectTechnique(Iro2GlassEquiRectTechnique::ES2, this);

    addTechnique(m_gl3Technique);
    addTechnique(m_es3Technique);
    addTechnique(m_es2Technique);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_rhiTechnique = new Iro2GlassEquiRectTechnique(Iro2GlassEquiRectTechnique::RHI, this);
    addTechnique(m_rhiTechnique);
#endif
}

Iro2GlassEquiRectEffect::~Iro2GlassEquiRectEffect() = default;


void Iro2GlassEquiRectEffect::updateDoubleSided(bool doubleSided)
{
    const auto cullingMode = doubleSided ? QCullFace::NoCulling : QCullFace::Back;
    m_gl3Technique->setCullingMode(cullingMode);
    m_es3Technique->setCullingMode(cullingMode);
    m_es2Technique->setCullingMode(cullingMode);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_rhiTechnique->setCullingMode(cullingMode);
#endif
}

void Iro2GlassEquiRectEffect::updateUsingSkinning(bool useSkinning)
{
    // Set Layers on zFill and opaque/Transparent shader builders
    auto layers = m_gl3Technique->enabledLayers();
    if (useSkinning) {
        layers.removeAll(QStringLiteral("no-skinning"));
        layers.append(QStringLiteral("skinning"));
    } else {
        layers.removeAll(QStringLiteral("skinning"));
        layers.append(QStringLiteral("no-skinning"));
    }

    updateLayersOnTechniques(layers);

    m_gl3Technique->setAllowCulling(!useSkinning);
    m_es3Technique->setAllowCulling(!useSkinning);
    m_es2Technique->setAllowCulling(!useSkinning);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_rhiTechnique->setAllowCulling(!useSkinning);
#endif
}

void Iro2GlassEquiRectEffect::updateOpaque(bool opaque)
{
    m_gl3Technique->setOpaque(opaque);
    m_es3Technique->setOpaque(opaque);
    m_es2Technique->setOpaque(opaque);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    m_rhiTechnique->setOpaque(opaque);
#endif
}

void Iro2GlassEquiRectEffect::updateAlphaCutoffEnabled(bool enabled)
{
    auto layers = m_gl3Technique->enabledLayers();
    if (enabled) {
        layers.removeAll(QStringLiteral("noHasAlphaCutoff"));
        layers.append(QStringLiteral("hasAlphaCutoff"));
    } else {
        layers.removeAll(QStringLiteral("hasAlphaCutoff"));
        layers.append(QStringLiteral("noHasAlphaCutoff"));
    }
    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingColorAttribute(bool usingColorAttribute)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("noHasColorAttr"));
    layers.removeAll(QStringLiteral("hasColorAttr"));
    layers.removeAll(QStringLiteral("hasVertexColor"));
    if (usingColorAttribute) {
        layers.append(QStringLiteral("hasColorAttr"));
        layers.append(QStringLiteral("hasVertexColor"));
    } else {
        layers.append(QStringLiteral("noHasColorAttr"));
    }
    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingNormalAttribute(bool usingNormalAttribute)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("hasVertexNormal"));
    if (usingNormalAttribute)
        layers.append(QStringLiteral("hasVertexNormal"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingTangentAttribute(bool usingTangentAttribute)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("hasVertexTangent"));
    if (usingTangentAttribute)
        layers.append(QStringLiteral("hasVertexTangent"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingTexCoordAttribute(bool usingTexCoordAttribute)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("hasTexCoord"));
    if (usingTexCoordAttribute)
        layers.append(QStringLiteral("hasTexCoord"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingTexCoord1Attribute(bool usingTexCoord1Attribute)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("hasTexCoord1"));
    if (usingTexCoord1Attribute)
        layers.append(QStringLiteral("hasTexCoord1"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateUsingMorphTargets(bool usingMorphTargets)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("morphtargets"));
    if (usingMorphTargets)
        layers.append(QStringLiteral("morphtargets"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateInstanced(bool instanced)
{
    auto layers = m_gl3Technique->enabledLayers();
    layers.removeAll(QStringLiteral("instanced"));
    if (instanced)
        layers.append(QStringLiteral("instanced"));

    updateLayersOnTechniques(layers);
}

void Iro2GlassEquiRectEffect::updateLayersOnTechniques(const QStringList &layers)
{
    m_gl3Technique->setEnabledLayers(layers);
    m_es3Technique->setEnabledLayers(layers);
    m_es2Technique->setEnabledLayers(layers);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    m_rhiTechnique->setEnabledLayers(layers);
#endif
}


} // namespace Kuesa

QT_END_NAMESPACE
