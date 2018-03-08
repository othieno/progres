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
# along with this program. If not, see <http://www.gnu.org/licenses/>.
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/VisualScriptItem.hh \
    $$PWD/VisualScriptNode.hh \
    $$PWD/VisualScriptWire.hh \
    $$PWD/VisualScript.hh

SOURCES += \
    $$PWD/VisualScriptItem.cc \
    $$PWD/VisualScriptNode.cc \
    $$PWD/VisualScriptWire.cc \
    $$PWD/VisualScript.cc

RESOURCES += $$PWD/visual.qrc
