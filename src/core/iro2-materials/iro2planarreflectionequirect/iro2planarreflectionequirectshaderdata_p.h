
/*
    iro2planarreflectionequirectshaderdata_p.h

    This file is part of Kuesa.

    Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef KUESA_IRO2PLANARREFLECTIONEQUIRECTSHADERDATA_P_H
#define KUESA_IRO2PLANARREFLECTIONEQUIRECTSHADERDATA_P_H


//
//  W A R N I N G
//  -------------
//
// This file is not part of the Kuesa API.  It exists for the convenience
// of other Kuesa classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QVector2D>
#include <QVector3D>
#include <Qt3DRender/QShaderData>

QT_BEGIN_NAMESPACE

namespace Kuesa {

class Iro2PlanarReflectionEquiRectShaderData : public Qt3DRender::QShaderData
{
    Q_OBJECT
    Q_PROPERTY(float reflectionGain READ reflectionGain WRITE setReflectionGain NOTIFY reflectionGainChanged)
    Q_PROPERTY(QVector3D reflectionInnerFilter READ reflectionInnerFilter WRITE setReflectionInnerFilter NOTIFY reflectionInnerFilterChanged)
    Q_PROPERTY(QVector3D reflectionOuterFilter READ reflectionOuterFilter WRITE setReflectionOuterFilter NOTIFY reflectionOuterFilterChanged)
    Q_PROPERTY(float innerAlpha READ innerAlpha WRITE setInnerAlpha NOTIFY innerAlphaChanged)
    Q_PROPERTY(float outerAlpha READ outerAlpha WRITE setOuterAlpha NOTIFY outerAlphaChanged)
    Q_PROPERTY(float alphaGain READ alphaGain WRITE setAlphaGain NOTIFY alphaGainChanged)
    Q_PROPERTY(bool usesNormalMap READ usesNormalMap WRITE setUsesNormalMap NOTIFY usesNormalMapChanged)
    Q_PROPERTY(float normalMapGain READ normalMapGain WRITE setNormalMapGain NOTIFY normalMapGainChanged)
    Q_PROPERTY(QVector3D normalScaling READ normalScaling WRITE setNormalScaling NOTIFY normalScalingChanged)
    Q_PROPERTY(QVector2D normalDisturb READ normalDisturb WRITE setNormalDisturb NOTIFY normalDisturbChanged)
    Q_PROPERTY(float postVertexColor READ postVertexColor WRITE setPostVertexColor NOTIFY postVertexColorChanged)
    Q_PROPERTY(float postGain READ postGain WRITE setPostGain NOTIFY postGainChanged)
    Q_PROPERTY(bool gltfYUp READ gltfYUp WRITE setGltfYUp NOTIFY gltfYUpChanged)

public:
    explicit Iro2PlanarReflectionEquiRectShaderData(Qt3DCore::QNode *parent = nullptr);
    ~Iro2PlanarReflectionEquiRectShaderData();
    float reflectionGain() const;
    QVector3D reflectionInnerFilter() const;
    QVector3D reflectionOuterFilter() const;
    float innerAlpha() const;
    float outerAlpha() const;
    float alphaGain() const;
    bool usesNormalMap() const;
    float normalMapGain() const;
    QVector3D normalScaling() const;
    QVector2D normalDisturb() const;
    float postVertexColor() const;
    float postGain() const;
    bool gltfYUp() const;

public Q_SLOTS:
    void setReflectionGain(float reflectionGain);
    void setReflectionInnerFilter(const QVector3D &reflectionInnerFilter);
    void setReflectionOuterFilter(const QVector3D &reflectionOuterFilter);
    void setInnerAlpha(float innerAlpha);
    void setOuterAlpha(float outerAlpha);
    void setAlphaGain(float alphaGain);
    void setUsesNormalMap(bool usesNormalMap);
    void setNormalMapGain(float normalMapGain);
    void setNormalScaling(const QVector3D &normalScaling);
    void setNormalDisturb(const QVector2D &normalDisturb);
    void setPostVertexColor(float postVertexColor);
    void setPostGain(float postGain);
    void setGltfYUp(bool gltfYUp);

Q_SIGNALS:
    void reflectionGainChanged(float);
    void reflectionInnerFilterChanged(QVector3D);
    void reflectionOuterFilterChanged(QVector3D);
    void innerAlphaChanged(float);
    void outerAlphaChanged(float);
    void alphaGainChanged(float);
    void usesNormalMapChanged(bool);
    void normalMapGainChanged(float);
    void normalScalingChanged(QVector3D);
    void normalDisturbChanged(QVector2D);
    void postVertexColorChanged(float);
    void postGainChanged(float);
    void gltfYUpChanged(bool);

private:
    float m_reflectionGain;
    QVector3D m_reflectionInnerFilter;
    QVector3D m_reflectionOuterFilter;
    float m_innerAlpha;
    float m_outerAlpha;
    float m_alphaGain;
    bool m_usesNormalMap;
    float m_normalMapGain;
    QVector3D m_normalScaling;
    QVector2D m_normalDisturb;
    float m_postVertexColor;
    float m_postGain;
    bool m_gltfYUp;

};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_IRO2PLANARREFLECTIONEQUIRECTSHADERDATA_P_H
