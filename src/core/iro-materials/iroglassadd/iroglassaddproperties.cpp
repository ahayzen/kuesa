
/*
    iroglassaddproperties.cpp

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

#include "iroglassaddproperties.h"
#include "iroglassaddshaderdata_p.h"
#include <Qt3DCore/private/qnode_p.h>
#include <Kuesa/private/empty2dtexture_p.h>


QT_BEGIN_NAMESPACE

using namespace Qt3DRender;

namespace Kuesa {


/*!
    \class Kuesa::IroGlassAddProperties
    \inheaderfile Kuesa/IroGlassAddProperties
    \inherits Kuesa::GLTF2MaterialProperties
    \inmodule Kuesa
    \since Kuesa 1.2

    \brief Kuesa::IroGlassAddProperties holds the properties controlling the visual appearance of a IroGlassAddMaterial instance.
*/

/*!
    \qmltype IroGlassAddProperties
    \instantiates Kuesa::IroGlassAddProperties
    \inqmlmodule Kuesa
    \since Kuesa 1.2

    \brief Kuesa::IroGlassAddProperties holds the properties controlling the visual appearance of a IroGlassAddMaterial instance.
*/

IroGlassAddProperties::IroGlassAddProperties(Qt3DCore::QNode *parent)
    : GLTF2MaterialProperties(parent)
    , m_shaderData(new IroGlassAddShaderData(this))
    , m_reflectionMap(nullptr)
{
    QObject::connect(m_shaderData, &IroGlassAddShaderData::normalScalingChanged, this, &IroGlassAddProperties::normalScalingChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::normalDisturbChanged, this, &IroGlassAddProperties::normalDisturbChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::postVertexColorChanged, this, &IroGlassAddProperties::postVertexColorChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::postGainChanged, this, &IroGlassAddProperties::postGainChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::reflectionGainChanged, this, &IroGlassAddProperties::reflectionGainChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::reflectionInnerFilterChanged, this, &IroGlassAddProperties::reflectionInnerFilterChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::reflectionOuterFilterChanged, this, &IroGlassAddProperties::reflectionOuterFilterChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::usesReflectionMapChanged, this, &IroGlassAddProperties::usesReflectionMapChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::projectReflectionMapChanged, this, &IroGlassAddProperties::projectReflectionMapChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::glassInnerFilterChanged, this, &IroGlassAddProperties::glassInnerFilterChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::glassOuterFilterChanged, this, &IroGlassAddProperties::glassOuterFilterChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::diffuseInnerFilterChanged, this, &IroGlassAddProperties::diffuseInnerFilterChanged);
    QObject::connect(m_shaderData, &IroGlassAddShaderData::diffuseOuterFilterChanged, this, &IroGlassAddProperties::diffuseOuterFilterChanged);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    setReflectionMap(new Empty2DTexture());
#endif
}

IroGlassAddProperties::~IroGlassAddProperties() = default;

Qt3DRender::QShaderData *IroGlassAddProperties::shaderData() const
{
    return m_shaderData;
}

void IroGlassAddProperties::setNormalScaling(const QVector3D &normalScaling)
{
    m_shaderData->setNormalScaling(normalScaling);
}

void IroGlassAddProperties::setNormalDisturb(const QVector2D &normalDisturb)
{
    m_shaderData->setNormalDisturb(normalDisturb);
}

void IroGlassAddProperties::setPostVertexColor(float postVertexColor)
{
    m_shaderData->setPostVertexColor(postVertexColor);
}

void IroGlassAddProperties::setPostGain(float postGain)
{
    m_shaderData->setPostGain(postGain);
}

void IroGlassAddProperties::setReflectionGain(float reflectionGain)
{
    m_shaderData->setReflectionGain(reflectionGain);
}

void IroGlassAddProperties::setReflectionInnerFilter(const QVector3D &reflectionInnerFilter)
{
    m_shaderData->setReflectionInnerFilter(reflectionInnerFilter);
}

void IroGlassAddProperties::setReflectionOuterFilter(const QVector3D &reflectionOuterFilter)
{
    m_shaderData->setReflectionOuterFilter(reflectionOuterFilter);
}

void IroGlassAddProperties::setUsesReflectionMap(bool usesReflectionMap)
{
    m_shaderData->setUsesReflectionMap(usesReflectionMap);
}

void IroGlassAddProperties::setProjectReflectionMap(bool projectReflectionMap)
{
    m_shaderData->setProjectReflectionMap(projectReflectionMap);
}

void IroGlassAddProperties::setGlassInnerFilter(const QVector3D &glassInnerFilter)
{
    m_shaderData->setGlassInnerFilter(glassInnerFilter);
}

void IroGlassAddProperties::setGlassOuterFilter(const QVector3D &glassOuterFilter)
{
    m_shaderData->setGlassOuterFilter(glassOuterFilter);
}

void IroGlassAddProperties::setDiffuseInnerFilter(const QVector3D &diffuseInnerFilter)
{
    m_shaderData->setDiffuseInnerFilter(diffuseInnerFilter);
}

void IroGlassAddProperties::setDiffuseOuterFilter(const QVector3D &diffuseOuterFilter)
{
    m_shaderData->setDiffuseOuterFilter(diffuseOuterFilter);
}

void IroGlassAddProperties::setReflectionMap(Qt3DRender::QAbstractTexture * reflectionMap)
{
    if (m_reflectionMap == reflectionMap)
        return;

    Qt3DCore::QNodePrivate *d = Qt3DCore::QNodePrivate::get(this);
    if (m_reflectionMap != nullptr)
        d->unregisterDestructionHelper(m_reflectionMap);
    m_reflectionMap = reflectionMap;
    if (m_reflectionMap != nullptr) {
        if (m_reflectionMap->parent() == nullptr)
            m_reflectionMap->setParent(this);
        d->registerDestructionHelper(m_reflectionMap, &IroGlassAddProperties::setReflectionMap, m_reflectionMap);
    }
    emit reflectionMapChanged(m_reflectionMap);
}


/*!
    \qmlproperty QVector3D IroGlassAddProperties::normalScaling
    Specifies a factor to be applied to the normal.
*/
/*!
    \property IroGlassAddProperties::normalScaling
    Specifies a factor to be applied to the normal.
*/
QVector3D IroGlassAddProperties::normalScaling() const
{
    return m_shaderData->normalScaling();
}

/*!
    \qmlproperty QVector2D IroGlassAddProperties::normalDisturb
    Specifies a disturbance factor that will be added to the normal
*/
/*!
    \property IroGlassAddProperties::normalDisturb
    Specifies a disturbance factor that will be added to the normal
*/
QVector2D IroGlassAddProperties::normalDisturb() const
{
    return m_shaderData->normalDisturb();
}

/*!
    \qmlproperty float IroGlassAddProperties::postVertexColor
    Specifies the factor which controls how much of the per vertex color we want to transmit.
*/
/*!
    \property IroGlassAddProperties::postVertexColor
    Specifies the factor which controls how much of the per vertex color we want to transmit.
*/
float IroGlassAddProperties::postVertexColor() const
{
    return m_shaderData->postVertexColor();
}

/*!
    \qmlproperty float IroGlassAddProperties::postGain
    Specifies the gain factor to be applied to the final result.
*/
/*!
    \property IroGlassAddProperties::postGain
    Specifies the gain factor to be applied to the final result.
*/
float IroGlassAddProperties::postGain() const
{
    return m_shaderData->postGain();
}

/*!
    \qmlproperty float IroGlassAddProperties::reflectionGain
    Specifies the gain factor to be applied to the spherical environment map lookup.
*/
/*!
    \property IroGlassAddProperties::reflectionGain
    Specifies the gain factor to be applied to the spherical environment map lookup.
*/
float IroGlassAddProperties::reflectionGain() const
{
    return m_shaderData->reflectionGain();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::reflectionInnerFilter
    Specifies the inner color filter to be applied based on fresnel on the spherical environment map lookup.
*/
/*!
    \property IroGlassAddProperties::reflectionInnerFilter
    Specifies the inner color filter to be applied based on fresnel on the spherical environment map lookup.
*/
QVector3D IroGlassAddProperties::reflectionInnerFilter() const
{
    return m_shaderData->reflectionInnerFilter();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::reflectionOuterFilter
    Specifies the outer color filter to be applied based on fresnel on the spherical environment map lookup.
*/
/*!
    \property IroGlassAddProperties::reflectionOuterFilter
    Specifies the outer color filter to be applied based on fresnel on the spherical environment map lookup.
*/
QVector3D IroGlassAddProperties::reflectionOuterFilter() const
{
    return m_shaderData->reflectionOuterFilter();
}

/*!
    \qmlproperty bool IroGlassAddProperties::usesReflectionMap
    Specifies whether we use a reflection map or not.
*/
/*!
    \property IroGlassAddProperties::usesReflectionMap
    Specifies whether we use a reflection map or not.
*/
bool IroGlassAddProperties::usesReflectionMap() const
{
    return m_shaderData->usesReflectionMap();
}

/*!
    \qmlproperty bool IroGlassAddProperties::projectReflectionMap
    Specifies whether equirectangular projection should be used for lookups on the reflection map.
*/
/*!
    \property IroGlassAddProperties::projectReflectionMap
    Specifies whether equirectangular projection should be used for lookups on the reflection map.
*/
bool IroGlassAddProperties::projectReflectionMap() const
{
    return m_shaderData->projectReflectionMap();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::glassInnerFilter
    Specifies the glass inner color filter to be applied based on fresnel.
*/
/*!
    \property IroGlassAddProperties::glassInnerFilter
    Specifies the glass inner color filter to be applied based on fresnel.
*/
QVector3D IroGlassAddProperties::glassInnerFilter() const
{
    return m_shaderData->glassInnerFilter();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::glassOuterFilter
    Specifies the glass outer color filter to be applied based on fresnel.
*/
/*!
    \property IroGlassAddProperties::glassOuterFilter
    Specifies the glass outer color filter to be applied based on fresnel.
*/
QVector3D IroGlassAddProperties::glassOuterFilter() const
{
    return m_shaderData->glassOuterFilter();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::diffuseInnerFilter
    Specifies the inner color filter to be applied based on fresnel on the diffuse map lookup.
*/
/*!
    \property IroGlassAddProperties::diffuseInnerFilter
    Specifies the inner color filter to be applied based on fresnel on the diffuse map lookup.
*/
QVector3D IroGlassAddProperties::diffuseInnerFilter() const
{
    return m_shaderData->diffuseInnerFilter();
}

/*!
    \qmlproperty QVector3D IroGlassAddProperties::diffuseOuterFilter
    Specifies the outer color filter to be applied based on fresnel on the diffuse map lookup.
*/
/*!
    \property IroGlassAddProperties::diffuseOuterFilter
    Specifies the outer color filter to be applied based on fresnel on the diffuse map lookup.
*/
QVector3D IroGlassAddProperties::diffuseOuterFilter() const
{
    return m_shaderData->diffuseOuterFilter();
}

Qt3DRender::QAbstractTexture * IroGlassAddProperties::reflectionMap() const
{
    return m_reflectionMap;
}


} // namespace Kuesa

QT_END_NAMESPACE
