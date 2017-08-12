/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017, Jeremy Othieno.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PROGRES_TESTSUITE_HH
#define PROGRES_TESTSUITE_HH

#include "Test.hh"

//TODO Change to nested namespace progres::testsuite
namespace progres {
namespace testsuite {
/**
 * Runs a set of tests.
 */
template<class... Tests>
int run(int argc, char** argv) {
    // The parent object is used to manage the dynamically allocated memory
    // for each test object, i.e. when it goes out of scope and is destroyed,
    // each test object attached to it will be destroyed too.

    // TODO This approach is flawed when the number of test objects becomes huge...
    QObject parent;
    const std::initializer_list<Test*> tests = {new Tests(parent)...};

    int exitStatus = 0;
    for (auto* const test : tests) {
        exitStatus |= QTest::qExec(test, argc, argv);
    }
    return exitStatus;
}
} // namespace testsuite
} // namespace progres

#endif // PROGRES_TESTSUITE_HH
