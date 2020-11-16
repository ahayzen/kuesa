
/*
    iro2glassequirectshaderdata.cpp

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "iro2glassequirectshaderdata_p.h"


QT_BEGIN_NAMESPACE

using namespace Qt3DRender;

namespace Kuesa {

Iro2GlassEquiRectShaderData::Iro2GlassEquiRectShaderData(Qt3DCore::QNode *parent)
    : Qt3DRender::QShaderData(parent)
    , m_glassInnerFilter()
    , m_glassOuterFilter()
    , m_usesReflectionMap()
    , m_reflectionGain()
    , m_reflectionInnerFilter()
    , m_reflectionOuterFilter()
    , m_usesNormalMap()
    , m_normalMapGain()
    , m_normalScaling()
    , m_normalDisturb()
    , m_postVertexColor()
    , m_postGain()
    , m_gltfYUp()
{}

Iro2GlassEquiRectShaderData::~Iro2GlassEquiRectShaderData() = default;

QVector3D Iro2GlassEquiRectShaderData::glassInnerFilter() const
{
    return m_glassInnerFilter;
}

QVector3D Iro2GlassEquiRectShaderData::glassOuterFilter() const
{
    return m_glassOuterFilter;
}

bool Iro2GlassEquiRectShaderData::usesReflectionMap() const
{
    return m_usesReflectionMap;
}

float Iro2GlassEquiRectShaderData::reflectionGain() const
{
    return m_reflectionGain;
}

QVector3D Iro2GlassEquiRectShaderData::reflectionInnerFilter() const
{
    return m_reflectionInnerFilter;
}

QVector3D Iro2GlassEquiRectShaderData::reflectionOuterFilter() const
{
    return m_reflectionOuterFilter;
}

bool Iro2GlassEquiRectShaderData::usesNormalMap() const
{
    return m_usesNormalMap;
}

float Iro2GlassEquiRectShaderData::normalMapGain() const
{
    return m_normalMapGain;
}

QVector3D Iro2GlassEquiRectShaderData::normalScaling() const
{
    return m_normalScaling;
}

QVector2D Iro2GlassEquiRectShaderData::normalDisturb() const
{
    return m_normalDisturb;
}

float Iro2GlassEquiRectShaderData::postVertexColor() const
{
    return m_postVertexColor;
}

float Iro2GlassEquiRectShaderData::postGain() const
{
    return m_postGain;
}

bool Iro2GlassEquiRectShaderData::gltfYUp() const
{
    return m_gltfYUp;
}


void Iro2GlassEquiRectShaderData::setGlassInnerFilter(const QVector3D &glassInnerFilter)
{
    if (m_glassInnerFilter == glassInnerFilter)
        return;
    m_glassInnerFilter = glassInnerFilter;
    emit glassInnerFilterChanged(glassInnerFilter);
}

void Iro2GlassEquiRectShaderData::setGlassOuterFilter(const QVector3D &glassOuterFilter)
{
    if (m_glassOuterFilter == glassOuterFilter)
        return;
    m_glassOuterFilter = glassOuterFilter;
    emit glassOuterFilterChanged(glassOuterFilter);
}

void Iro2GlassEquiRectShaderData::setUsesReflectionMap(bool usesReflectionMap)
{
    if (m_usesReflectionMap == usesReflectionMap)
        return;
    m_usesReflectionMap = usesReflectionMap;
    emit usesReflectionMapChanged(usesReflectionMap);
}

void Iro2GlassEquiRectShaderData::setReflectionGain(float reflectionGain)
{
    if (m_reflectionGain == reflectionGain)
        return;
    m_reflectionGain = reflectionGain;
    emit reflectionGainChanged(reflectionGain);
}

void Iro2GlassEquiRectShaderData::setReflectionInnerFilter(const QVector3D &reflectionInnerFilter)
{
    if (m_reflectionInnerFilter == reflectionInnerFilter)
        return;
    m_reflectionInnerFilter = reflectionInnerFilter;
    emit reflectionInnerFilterChanged(reflectionInnerFilter);
}

void Iro2GlassEquiRectShaderData::setReflectionOuterFilter(const QVector3D &reflectionOuterFilter)
{
    if (m_reflectionOuterFilter == reflectionOuterFilter)
        return;
    m_reflectionOuterFilter = reflectionOuterFilter;
    emit reflectionOuterFilterChanged(reflectionOuterFilter);
}

void Iro2GlassEquiRectShaderData::setUsesNormalMap(bool usesNormalMap)
{
    if (m_usesNormalMap == usesNormalMap)
        return;
    m_usesNormalMap = usesNormalMap;
    emit usesNormalMapChanged(usesNormalMap);
}

void Iro2GlassEquiRectShaderData::setNormalMapGain(float normalMapGain)
{
    if (m_normalMapGain == normalMapGain)
        return;
    m_normalMapGain = normalMapGain;
    emit normalMapGainChanged(normalMapGain);
}

void Iro2GlassEquiRectShaderData::setNormalScaling(const QVector3D &normalScaling)
{
    if (m_normalScaling == normalScaling)
        return;
    m_normalScaling = normalScaling;
    emit normalScalingChanged(normalScaling);
}

void Iro2GlassEquiRectShaderData::setNormalDisturb(const QVector2D &normalDisturb)
{
    if (m_normalDisturb == normalDisturb)
        return;
    m_normalDisturb = normalDisturb;
    emit normalDisturbChanged(normalDisturb);
}

void Iro2GlassEquiRectShaderData::setPostVertexColor(float postVertexColor)
{
    if (m_postVertexColor == postVertexColor)
        return;
    m_postVertexColor = postVertexColor;
    emit postVertexColorChanged(postVertexColor);
}

void Iro2GlassEquiRectShaderData::setPostGain(float postGain)
{
    if (m_postGain == postGain)
        return;
    m_postGain = postGain;
    emit postGainChanged(postGain);
}

void Iro2GlassEquiRectShaderData::setGltfYUp(bool gltfYUp)
{
    if (m_gltfYUp == gltfYUp)
        return;
    m_gltfYUp = gltfYUp;
    emit gltfYUpChanged(gltfYUp);
}



} // namespace Kuesa

QT_END_NAMESPACE