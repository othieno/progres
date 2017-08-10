# This file is part of PROGRES (Procedural Graphics Editor Suite).
# Copyright (C) 2017, Jeremy Othieno.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

greaterThan(QT_MAJOR_VERSION, 4):greaterThan(QT_MINOR_VERSION, 7) {
    APPLICATION_NAME = "PROGRES"
    APPLICATION_VERSION = 0.0.0
    APPLICATION_REPOSITORY = "https://github.com/othieno/progres"
    DEFINES += \
        APPLICATION_NAME=\\\"$$APPLICATION_NAME\\\" \
        APPLICATION_VERSION=\\\"$$APPLICATION_VERSION\\\" \
        APPLICATION_REPOSITORY=\\\"$$APPLICATION_REPOSITORY\\\"

    QT += qml quick
    CONFIG += c++14
    QMAKE_CXXFLAGS += -Wall -Wextra -ansi -pedantic-errors -Werror

    DESTDIR = build
    OBJECTS_DIR = $${DESTDIR}/obj
    MOC_DIR = $${DESTDIR}/moc
    RCC_DIR = $${DESTDIR}/rcc
    UI_DIR = $${DESTDIR}/ui

    INCLUDEPATH += \
        src/graphics \
        src/scripting \
        src/system \
        src/ui

    HEADERS += \
        src/system/Application.hh \
        src/system/Error.hh

    SOURCES += \
        src/system/Application.cc \
        src/system/Error.cc \
        src/progres.cc

} else {
    error(\
        "Building PROGRES requires Qt 5.8"\
        "Make sure your version of qmake is using the Qt 5.8 libraries, or later." \
        "You can find out which version is currently being used by running 'qmake --version'."\
    )
}
