
/*
    iroglassaddshaderdata.cpp

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

#include "iroglassaddshaderdata_p.h"
#include <Qt3DCore/private/qnode_p.h>


QT_BEGIN_NAMESPACE

using namespace Qt3DRender;

namespace Kuesa {

IroGlassAddShaderData::IroGlassAddShaderData(Qt3DCore::QNode *parent)
    : Qt3DRender::QShaderData(parent)
    , m_normalScaling()
    , m_normalDisturb()
    , m_postVertexColor()
    , m_postGain()
    , m_reflectionGain()
    , m_reflectionMap(nullptr)
    , m_reflectionInnerFilter()
    , m_reflectionOuterFilter()
    , m_reflectionInnerAlpha()
    , m_reflectionOuterAlpha()
    , m_glassInnerFilter()
    , m_glassOuterFilter()
{}

IroGlassAddShaderData::~IroGlassAddShaderData() = default;

QVector3D IroGlassAddShaderData::normalScaling() const
{
    return m_normalScaling;
}

QVector2D IroGlassAddShaderData::normalDisturb() const
{
    return m_normalDisturb;
}

float IroGlassAddShaderData::postVertexColor() const
{
    return m_postVertexColor;
}

float IroGlassAddShaderData::postGain() const
{
    return m_postGain;
}

float IroGlassAddShaderData::reflectionGain() const
{
    return m_reflectionGain;
}

Qt3DRender::QAbstractTexture * IroGlassAddShaderData::reflectionMap() const
{
    return m_reflectionMap;
}

QVector3D IroGlassAddShaderData::reflectionInnerFilter() const
{
    return m_reflectionInnerFilter;
}

QVector3D IroGlassAddShaderData::reflectionOuterFilter() const
{
    return m_reflectionOuterFilter;
}

float IroGlassAddShaderData::reflectionInnerAlpha() const
{
    return m_reflectionInnerAlpha;
}

float IroGlassAddShaderData::reflectionOuterAlpha() const
{
    return m_reflectionOuterAlpha;
}

QVector3D IroGlassAddShaderData::glassInnerFilter() const
{
    return m_glassInnerFilter;
}

QVector3D IroGlassAddShaderData::glassOuterFilter() const
{
    return m_glassOuterFilter;
}


void IroGlassAddShaderData::setNormalScaling(const QVector3D &normalScaling)
{
    if (m_normalScaling == normalScaling)
        return;
    m_normalScaling = normalScaling;
    emit normalScalingChanged(normalScaling);
}

void IroGlassAddShaderData::setNormalDisturb(const QVector2D &normalDisturb)
{
    if (m_normalDisturb == normalDisturb)
        return;
    m_normalDisturb = normalDisturb;
    emit normalDisturbChanged(normalDisturb);
}

void IroGlassAddShaderData::setPostVertexColor(float postVertexColor)
{
    if (m_postVertexColor == postVertexColor)
        return;
    m_postVertexColor = postVertexColor;
    emit postVertexColorChanged(postVertexColor);
}

void IroGlassAddShaderData::setPostGain(float postGain)
{
    if (m_postGain == postGain)
        return;
    m_postGain = postGain;
    emit postGainChanged(postGain);
}

void IroGlassAddShaderData::setReflectionGain(float reflectionGain)
{
    if (m_reflectionGain == reflectionGain)
        return;
    m_reflectionGain = reflectionGain;
    emit reflectionGainChanged(reflectionGain);
}

void IroGlassAddShaderData::setReflectionMap(Qt3DRender::QAbstractTexture * reflectionMap)
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
        d->registerDestructionHelper(m_reflectionMap, &IroGlassAddShaderData::setReflectionMap, m_reflectionMap);
    }
    emit reflectionMapChanged(m_reflectionMap);
}

void IroGlassAddShaderData::setReflectionInnerFilter(const QVector3D &reflectionInnerFilter)
{
    if (m_reflectionInnerFilter == reflectionInnerFilter)
        return;
    m_reflectionInnerFilter = reflectionInnerFilter;
    emit reflectionInnerFilterChanged(reflectionInnerFilter);
}

void IroGlassAddShaderData::setReflectionOuterFilter(const QVector3D &reflectionOuterFilter)
{
    if (m_reflectionOuterFilter == reflectionOuterFilter)
        return;
    m_reflectionOuterFilter = reflectionOuterFilter;
    emit reflectionOuterFilterChanged(reflectionOuterFilter);
}

void IroGlassAddShaderData::setReflectionInnerAlpha(float reflectionInnerAlpha)
{
    if (m_reflectionInnerAlpha == reflectionInnerAlpha)
        return;
    m_reflectionInnerAlpha = reflectionInnerAlpha;
    emit reflectionInnerAlphaChanged(reflectionInnerAlpha);
}

void IroGlassAddShaderData::setReflectionOuterAlpha(float reflectionOuterAlpha)
{
    if (m_reflectionOuterAlpha == reflectionOuterAlpha)
        return;
    m_reflectionOuterAlpha = reflectionOuterAlpha;
    emit reflectionOuterAlphaChanged(reflectionOuterAlpha);
}

void IroGlassAddShaderData::setGlassInnerFilter(const QVector3D &glassInnerFilter)
{
    if (m_glassInnerFilter == glassInnerFilter)
        return;
    m_glassInnerFilter = glassInnerFilter;
    emit glassInnerFilterChanged(glassInnerFilter);
}

void IroGlassAddShaderData::setGlassOuterFilter(const QVector3D &glassOuterFilter)
{
    if (m_glassOuterFilter == glassOuterFilter)
        return;
    m_glassOuterFilter = glassOuterFilter;
    emit glassOuterFilterChanged(glassOuterFilter);
}



} // namespace Kuesa

QT_END_NAMESPACE