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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import qbs
import qbs.FileInfo

DynamicLibrary {
	readonly property string installDir: FileInfo.joinPaths(project.qmlPluginInstallDir, path)
	readonly property string uri: path.replace(/\//g, '.')
	property string path

	cpp.cxxFlags: [
		"-pedantic-errors",
	]
	cpp.cxxLanguageVersion: "c++14"
	cpp.defines: [
		'PLUGIN_URI="' + product.uri + '"',
		'QT_DEPRECATED_WARNINGS',
		'QT_NO_CAST_FROM_ASCII',
		'QT_NO_CAST_TO_ASCII',
	]
	cpp.enableExceptions: false
	cpp.enableRtti: false
	cpp.linkerFlags: [
		"--no-undefined",
	]
	cpp.treatWarningsAsErrors: true

	FileTagger {
		patterns: "*.hh"
		fileTags: "hpp"
	}
	FileTagger {
		patterns: [
			"qmldir",
			"*.qml",
			"*.qmltypes",
		]
		fileTags: "qml"
	}

	Depends {
		name: "Qt"
		submodules: [
			"qml",
			"quick",
		]
		versionAtLeast: project.minimumQtVersion
	}

	// Group {
	// 	name: "QML Resource Data"
	// 	fileTags: "qt.core.resource_data"
	// 	fileTagsFilter: "qml"
	// }

	Group {
		qbs.install: true
		qbs.installDir: product.installDir
		fileTagsFilter: [
			"dynamiclibrary",
			"qml",
		]
	}

	Export {
		Depends {
			name: "cpp"
		}
		cpp.includePaths: product.sourceDirectory
	}
}
