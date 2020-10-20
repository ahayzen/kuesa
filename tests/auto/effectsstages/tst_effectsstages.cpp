/*
    tst_effectsstages.cpp

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

#include <QtTest/QtTest>

#include <Qt3DRender/QTechniqueFilter>
#include <Qt3DRender/QFrustumCulling>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QLayerFilter>
#include <Qt3DRender/QRenderTarget>
#include <Qt3DRender/QRenderTargetSelector>
#include <Qt3DRender/QTexture>

#include <Kuesa/forwardrenderer.h>
#include <Kuesa/abstractpostprocessingeffect.h>
#include <Kuesa/private/effectsstages_p.h>

namespace {

class tst_FX : public Kuesa::AbstractPostProcessingEffect
{
    Q_OBJECT

public:
    explicit tst_FX(Qt3DCore::QNode *parent = nullptr)
        : Kuesa::AbstractPostProcessingEffect(parent)
        , m_rootNode(new Qt3DRender::QFrameGraphNode())
        , m_inputTexture(nullptr)
    {
    }

    // AbstractPostProcessingEffect interface
    FrameGraphNodePtr frameGraphSubTree() const override
    {
        return m_rootNode;
    }

    QVector<Qt3DRender::QLayer *> layers() const override
    {
        return QVector<Qt3DRender::QLayer *>();
    }

    void setInputTexture(Qt3DRender::QAbstractTexture *texture) override
    {
        m_inputTexture = texture;
    }

    Qt3DRender::QAbstractTexture *inputTexture() const
    {
        return m_inputTexture;
    }

    void setWindowSize(const QSize &size) override
    {
        emit sceneSizeChanged(size);
    }

Q_SIGNALS:
    void sceneSizeChanged(const QSize &size);

private:
    FrameGraphNodePtr m_rootNode;
    Qt3DRender::QAbstractTexture *m_inputTexture;
};

} // namespace

class tst_EffectsStages : public QObject
{
    Q_OBJECT
private Q_SLOTS:

    void checkDefaults()
    {
        // GIVEN
        Kuesa::EffectsStages e;

        // THEN
        std::pair<
                Qt3DRender::QRenderTarget *,
                Qt3DRender::QRenderTarget *> emptyRts = { nullptr, nullptr };
        QVERIFY(e.camera() == nullptr);
        QCOMPARE(e.renderTargets(), emptyRts);
        QVERIFY(e.depthTexture() == nullptr);
        QCOMPARE(e.viewport(), QRectF(0.0f, 0.0f, 1.0f, 1.0f));
        QCOMPARE(e.effects().size(), size_t(0));
        QCOMPARE(e.presentToScreen(), false);
    }

    void testCamera()
    {
        // GIVEN
        Kuesa::EffectsStages e;

        {
            // WHEN
            Qt3DCore::QEntity c;

            e.setCamera(&c);

            // THEN
            QCOMPARE(e.camera(), &c);
        }

        // THEN
        QVERIFY(e.camera() == nullptr);
    }

    void testAddFX()
    {
        // GIVEN
        Kuesa::EffectsStages e;

        {
            tst_FX fx;

            // WHEN
            e.addEffect(&fx);
            QCoreApplication::processEvents();

            // THEN
            QCOMPARE(e.effects().size(), 1U);
            QCOMPARE(e.effects().front(), &fx);
        }
        QCoreApplication::processEvents();

        // THEN
        QCOMPARE(e.effects().size(), 0U);
    }

    void testRemoveFX()
    {
        // GIVEN
        Kuesa::EffectsStages e;
        tst_FX fx;

        // WHEN
        e.addEffect(&fx);
        e.removeEffect(&fx);

        // THEN
        QCOMPARE(e.effects().size(), 0U);
    }

    void checkFrameGraph()
    {
        // GIVEN
        Kuesa::EffectsStages e;
        Qt3DRender::QRenderTarget rt0(&e);
        Qt3DRender::QRenderTarget rt1(&e);

        Qt3DRender::QRenderTargetOutput rt0Out;
        Qt3DRender::QRenderTargetOutput rt1Out;

        Qt3DRender::QTexture2D tex0;
        Qt3DRender::QTexture2D tex1;

        rt0Out.setTexture(&tex0);
        rt0Out.setAttachmentPoint(Qt3DRender::QRenderTargetOutput::Color0);

        rt1Out.setTexture(&tex1);
        rt1Out.setAttachmentPoint(Qt3DRender::QRenderTargetOutput::Color0);

        // THEN -> No FX, No RT, No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 0);
        }

        // WHEN
        tst_FX fx1;
        e.addEffect(&fx1);

        // THEN -> FX(1), Not RT, No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 0);
        }

        // WHEN
        e.setRenderTargets(&rt0, nullptr);

        // THEN -> FX(1), RT(1), No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 0);
        }

        // WHEN
        e.setRenderTargets(&rt0, &rt1);

        // THEN -> FX(1), RT(2), No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 1);
            Qt3DRender::QRenderTargetSelector *rtS = qobject_cast<Qt3DRender::QRenderTargetSelector *>(vp->children().first());
            QVERIFY(rtS != nullptr);
            QCOMPARE(rtS->children().size(), 1);
            QCOMPARE(rtS->children().last(), fx1.frameGraphSubTree().data());
            QCOMPARE(rtS->target(), &rt1);
        }

        // WHEN
        e.setRenderTargets(&rt0, nullptr);
        e.setPresentToScreen(true);

        // THEN -> FX(1), RT(1), Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 1);
            QCOMPARE(vp->children().first(), fx1.frameGraphSubTree().data());
        }

        // WHEN
        e.setPresentToScreen(false);
        tst_FX fx2;
        e.addEffect(&fx2);

        // THEN -> FX(2), RT(1), No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 0);
        }

        // WHEN
        e.setRenderTargets(&rt0, &rt1);

        // THEN -> FX(2), RT(2), No Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 2);
            Qt3DRender::QRenderTargetSelector *rtS0 = qobject_cast<Qt3DRender::QRenderTargetSelector *>(vp->children().first());
            Qt3DRender::QRenderTargetSelector *rtS1 = qobject_cast<Qt3DRender::QRenderTargetSelector *>(vp->children().last());
            QVERIFY(rtS0 != nullptr && rtS1 != nullptr);
            QCOMPARE(rtS0->children().size(), 1);
            QCOMPARE(rtS1->children().size(), 1);
            QCOMPARE(rtS0->children().first(), fx1.frameGraphSubTree().data());
            QCOMPARE(rtS1->children().first(), fx2.frameGraphSubTree().data());
            QCOMPARE(rtS0->target(), &rt1);
            QCOMPARE(rtS1->target(), &rt0);
        }

        // WHEN
        e.setPresentToScreen(true);

        // THEN -> FX(2), RT(2), Present to Screen
        {
            QCOMPARE(e.children().size(), 3);
            Qt3DRender::QViewport *vp = qobject_cast<Qt3DRender::QViewport *>(e.children().first());
            QCOMPARE(e.children().at(1), &rt0);
            QCOMPARE(e.children().at(2), &rt1);
            QVERIFY(vp != nullptr);
            QCOMPARE(vp->children().size(), 2);
            Qt3DRender::QRenderTargetSelector *rtS = qobject_cast<Qt3DRender::QRenderTargetSelector *>(vp->children().first());
            QVERIFY(rtS != nullptr);
            QCOMPARE(rtS->children().size(), 1);
            QCOMPARE(rtS->children().first(), fx1.frameGraphSubTree().data());
            QCOMPARE(rtS->target(), &rt1);
            QCOMPARE(vp->children().last(), fx2.frameGraphSubTree().data());
        }
    }
};

QTEST_MAIN(tst_EffectsStages)
#include "tst_effectsstages.moc"