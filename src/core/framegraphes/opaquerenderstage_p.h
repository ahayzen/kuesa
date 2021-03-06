/*
    opaquerenderstage_p.h

    This file is part of Kuesa.

    Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Mike Krus <mike.krus@kdab.com>

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

#ifndef KUESA_OPAQUERENDERSTAGE_P_H
#define KUESA_OPAQUERENDERSTAGE_P_H

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

#include <Kuesa/private/kuesa_global_p.h>
#include "abstractrenderstage_p.h"
#include <Qt3DRender/QCullFace>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
class QDepthTest;
class QNoDepthMask;
class QRenderStateSet;
class QSortPolicy;
} // namespace Qt3DRender

namespace Kuesa {

class KUESA_PRIVATE_EXPORT OpaqueRenderStage : public AbstractRenderStage
{
    Q_OBJECT
public:
    explicit OpaqueRenderStage(Qt3DRender::QFrameGraphNode *parent = nullptr);
    ~OpaqueRenderStage();

    void setZFilling(bool zFill);
    bool zFilling() const;

    void setCullingMode(Qt3DRender::QCullFace::CullingMode mode);
    Qt3DRender::QCullFace::CullingMode cullingMode() const;

private:
    Qt3DRender::QRenderStateSet *m_states;
    Qt3DRender::QDepthTest *m_depthTest;
    Qt3DRender::QNoDepthMask *m_noDepthWrite;
    Qt3DRender::QSortPolicy *m_sortPolicy;
    Qt3DRender::QCullFace *m_cullFace;
};
} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_OPAQUERENDERSTAGE_P_H
