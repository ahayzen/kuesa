/*
    transformtracker.h

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef TRANSFORMTRACKER_H
#define TRANSFORMTRACKER_H

#include <Qt3DCore/qnode.h>
#include <Qt3DCore/qtransform.h>
#include <Kuesa/kuesa_global.h>
#include <Kuesa/sceneentity.h>

QT_BEGIN_NAMESPACE

namespace Kuesa {

class EntityTransformWatcher;

class KUESASHARED_EXPORT TransformTracker : public Qt3DCore::QNode
{
    Q_OBJECT
    Q_PROPERTY(Kuesa::SceneEntity *sceneEntity READ sceneEntity WRITE setSceneEntity NOTIFY sceneEntityChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(Qt3DCore::QEntity *camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(QSize screenSize READ screenSize WRITE setScreenSize NOTIFY screenSizeChanged)
    Q_PROPERTY(QMatrix4x4 matrix READ matrix NOTIFY matrixChanged)
    Q_PROPERTY(QMatrix4x4 worldMatrix READ worldMatrix NOTIFY worldMatrixChanged)
    Q_PROPERTY(QQuaternion rotation READ rotation NOTIFY rotationChanged)
    Q_PROPERTY(float rotationX READ rotationX NOTIFY rotationXChanged)
    Q_PROPERTY(float rotationY READ rotationY NOTIFY rotationYChanged)
    Q_PROPERTY(float rotationZ READ rotationZ NOTIFY rotationZChanged)
    Q_PROPERTY(float scale READ scale NOTIFY scaleChanged)
    Q_PROPERTY(QVector3D scale3D READ scale3D NOTIFY scale3DChanged)
    Q_PROPERTY(QVector3D translation READ translation NOTIFY translationChanged)
    Q_PROPERTY(QPointF screenPosition READ screenPosition NOTIFY screenPositionChanged)
public:
    explicit TransformTracker(Qt3DCore::QNode *parent = nullptr);
    ~TransformTracker();

    SceneEntity *sceneEntity() const;
    Qt3DCore::QEntity *camera() const;
    QSize screenSize() const;
    QString name() const;
    QMatrix4x4 matrix() const;
    QMatrix4x4 worldMatrix() const;
    QQuaternion rotation() const;
    float rotationX() const;
    float rotationY() const;
    float rotationZ() const;
    float scale() const;
    QVector3D scale3D() const;
    QVector3D translation() const;
    QPointF screenPosition() const;

public Q_SLOTS:
    void setName(const QString &name);
    void setSceneEntity(SceneEntity *sceneEntity);
    void setCamera(Qt3DCore::QEntity *camera);
    void setScreenSize(const QSize &screenSize);

Q_SIGNALS:
    void nameChanged(const QString &name);
    void sceneEntityChanged(const Kuesa::SceneEntity *sceneEntity);
    void cameraChanged(Qt3DCore::QEntity *camera);
    void screenSizeChanged(const QSize &screenSize);
    void scaleChanged(float scale);
    void scale3DChanged(const QVector3D &scale);
    void rotationChanged(const QQuaternion &rotation);
    void translationChanged(const QVector3D &translation);
    void matrixChanged();
    void rotationXChanged(float rotationX);
    void rotationYChanged(float rotationY);
    void rotationZChanged(float rotationZ);
    void worldMatrixChanged(const QMatrix4x4 &worldMatrix);
    void screenPositionChanged(const QPointF &screenPosition);

private:
    void updateSceneFromParent(Qt3DCore::QNode *parent);
    void matchNode();
    void updateScreenProjection();

    SceneEntity *m_sceneEntity;
    Qt3DCore::QEntity *m_camera;
    EntityTransformWatcher *m_cameraWatcher;
    Qt3DCore::QTransform *m_cameraTransform;
    Qt3DRender::QCameraLens *m_cameraLens;
    QSize m_screenSize;
    QString m_name;
    Qt3DCore::QTransform *m_node;
    EntityTransformWatcher *m_nodeWatcher;
    QPointF m_screenPosition;
};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // TRANSFORMTRACKER_H