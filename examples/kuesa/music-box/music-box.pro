# music-box.pro
#
# This file is part of Kuesa.
#
# Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
# Author: Mauro Persano <mauro.persano@kdab.com>
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

TEMPLATE = app

TARGET = music-box

QT += 3dcore 3drender 3dinput 3dextras 3dquick qml quick 3dquickextras 3danimation kuesa
SOURCES += \
    main.cpp \
    sampler.cpp

HEADERS += \
    sampler.h

RESOURCES += \
    qml/qml.qrc \
    ../assets/envmaps/pink_sunrise/envmap-pink-sunrise-16f.qrc \
    ../assets/models/music-box/music-box.qrc

install_music_samples.path = $$[QT_INSTALL_EXAMPLES]/kuesa/$$TARGET
install_music_samples.files = $$PWD/assets/samples

packagesExist(portaudio-2.0) {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
    DEFINES += KUESA_HAS_AUDIO=1
}

target.path = $$[QT_INSTALL_EXAMPLES]/kuesa/$$TARGET
INSTALLS += target

OTHER_FILES += doc/src/* \
    ../assets/models/music-box/music-box.qrc \
    ../assets/envmaps/pink_sunrise/envmap-pink-sunrise-16f.qrc
