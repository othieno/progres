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

include(../progres.pri)

TEMPLATE = app
TARGET = progres-testsuite
QT += testlib

# Remove progres.cc or this will create an entry point conflict: one main
# function in progres.cc and the other in testsuite.cc.
SOURCES -= src/progres.cc

# Prefix each path with "../".
paths       = $$INCLUDEPATH
headers     = $$HEADERS
sources     = $$SOURCES
INCLUDEPATH =
HEADERS     =
SOURCES     =
for (path, paths):     INCLUDEPATH += ../$$path
for (header, headers): HEADERS += ../$$header
for (source, sources): SOURCES += ../$$source
INCLUDEPATH += .
DESTDIR = ../$${DESTDIR}
OBJECTS_DIR = ../$${OBJECTS_DIR}
MOC_DIR = ../$${MOC_DIR}
RCC_DIR = ../$${RCC_DIR}
UI_DIR = ../$${UI_DIR}

HEADERS += \
    testsuite.hh

SOURCES += \
    testsuite.cc

include(../vendor/fluid/fluid.pri)
