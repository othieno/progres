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

include(progres.pri)
include(vendor/fluid/fluid.pri)

TEMPLATE = app
TARGET = progres
RESOURCES += progres.qrc

# Add a Makefile target to help build the documentation.
DOXYFILE = "$$PWD/progres.doxyfile"
documentation_target.target = doc
documentation_target.commands = @doxygen "$$DOXYFILE"
QMAKE_EXTRA_TARGETS += documentation_target

# Add Makefile targets to help build and run the testsuite.
TESTSUITE_DIR = "$$PWD/testsuite"
TESTSUITE_BIN = "$$PWD/build/progres-testsuite"
testsuite_target.target = tests
testsuite_target.commands = @qmake "$$TESTSUITE_DIR" -o "$$TESTSUITE_DIR/Makefile" && make -C "$$TESTSUITE_DIR"
run_testsuite_target.target = run-tests
run_testsuite_target.depends = testsuite_target
run_testsuite_target.commands = @"$$TESTSUITE_BIN"
QMAKE_EXTRA_TARGETS += testsuite_target run_testsuite_target
