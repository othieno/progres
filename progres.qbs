/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017-2018, Jeremy Othieno.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import qbs

Project {
	readonly property string repository: "https://github.com/othieno/progres"
	readonly property string version: "0.0.0"
	readonly property string minimumQtVersion: "5.10.0"

	name: "PROGRES"
	minimumQbsVersion: "1.10.0"
	qbsSearchPaths: [
		"vendor/fluid/qbs/shared",
	]
	references: [
		// "documentation/documentation.qbs",
		"src/src.qbs",
		// "testsuite/testsuite.qbs",
		"vendor/vendor.qbs",
	]
}
