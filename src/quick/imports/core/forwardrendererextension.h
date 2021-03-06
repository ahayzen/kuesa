/*
    forwardrenderextension.h

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

#ifndef KUESA_FORWARDRENDERER_EXTENSION_H
#define KUESA_FORWARDRENDERER_EXTENSION_H

#include <QObject>
#include <QtQml/QQmlListProperty>

QT_BEGIN_NAMESPACE

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
using qt_size_type = qsizetype;
#else
using qt_size_type = int;
#endif

namespace Kuesa {

class View;

class ForwardRendererExtension : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Kuesa::View> views READ views CONSTANT)
public:
    explicit ForwardRendererExtension(QObject *parent = nullptr);

    QQmlListProperty<Kuesa::View> views();

private:
    static void appendView(QQmlListProperty<Kuesa::View> *list, Kuesa::View *layer);
    static Kuesa::View *viewAt(QQmlListProperty<Kuesa::View> *list, qt_size_type index);
    static qt_size_type viewCount(QQmlListProperty<Kuesa::View> *list);
    static void clearViews(QQmlListProperty<Kuesa::View> *list);
};

} // namespace Kuesa

QT_END_NAMESPACE

#endif // KUESA_FORWARDRENDERER_EXTENSION_H
