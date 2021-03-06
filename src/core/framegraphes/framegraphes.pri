# framegraphes.pri
#
# This file is part of Kuesa.
#
# Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
# Author: Mike Krus <mike.krus@kdab.com>
#
# Licensees holding valid proprietary KDAB Kuesa licenses may use this file in
# accordance with the Kuesa Enterprise License Agreement provided with the Software in the
# LICENSE.KUESA.ENTERPRISE file.
#
# Contact info@kdab.com if any conditions of this licensing are not clear to you.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/effectsstages.cpp \
    $$PWD/fboresolver.cpp \
    $$PWD/forwardrenderer.cpp \
    $$PWD/abstractrenderstage.cpp \
    $$PWD/framegraphutils.cpp \
    $$PWD/reflectionplane.cpp \
    $$PWD/reflectionstages.cpp \
    $$PWD/shadowmapstages.cpp \
    $$PWD/scenestages.cpp \
    $$PWD/view.cpp \
    $$PWD/viewresolver.cpp \
    $$PWD/zfillrenderstage.cpp \
    $$PWD/opaquerenderstage.cpp \
    $$PWD/transparentrenderstage.cpp \
    $$PWD/particlerenderstage.cpp

HEADERS += \
    $$PWD/effectsstages_p.h \
    $$PWD/fboresolver_p.h \
    $$PWD/forwardrenderer.h \
    $$PWD/abstractrenderstage_p.h \
    $$PWD/framegraphutils_p.h \
    $$PWD/reflectionplane.h \
    $$PWD/reflectionstages_p.h \
    $$PWD/shadowmapstages_p.h \
    $$PWD/scenestages_p.h \
    $$PWD/view.h \
    $$PWD/viewresolver_p.h \
    $$PWD/zfillrenderstage_p.h \
    $$PWD/opaquerenderstage_p.h \
    $$PWD/transparentrenderstage_p.h \
    $$PWD/particlerenderstage_p.h
