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
import qbs.Environment
import qbs.FileInfo
import qbs.ModUtils
import qbs.PathTools

Module {
	property path qmlPath

	setupRunEnvironment: {
		var env = Environment.currentEnv();

		env["QML2_IMPORT_PATH"] = PathTools.prependOrSetPath([
			FileInfo.joinPaths(qbs.installRoot, qbs.installPrefix, qmlPath)
		].join(qbs.pathListSeparator), env["QML2_IMPORT_PATH"], qbs.pathListSeparator);

		for (var i in env) {
			var v = new ModUtils.EnvironmentVariable(i, qbs.pathListSeparator, qbs.hostOS.contains("windows"));
			v.value = env[i];
			v.set();
		}
	}
}
