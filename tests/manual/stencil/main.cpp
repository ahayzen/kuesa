#include <QApplication>
#include <QStandardPaths>
#include <QDir>

#include <QSurfaceFormat>
#include <QQuickView>

#include "stencilhelper.h"
#include "stencileffect.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setDepthBufferSize(24);
    format.setSamples(4);
    format.setStencilBufferSize(8);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(4, 6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterType<StencilHelper>("Test", 1, 0, "StencilHelper");
    qmlRegisterType<StencilEffect>("Test", 1, 0, "StencilEffect");

    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);

    view.showMaximized();
    app.exec();
}
