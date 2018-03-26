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
	property string qmlPath: "qml"

	qbsSearchPaths: ".qbs"

	SubProject {
		filePath: "gui/plugins/visualscript/visualscript.qbs"
		Properties {
			qmlPluginInstallDir: qmlPath
		}
	}

	QtGuiApplication {
		Depends {name: "lirideployment"}
		Depends {name: "Fluid"}
		Depends {name: "VisualScript"}
		Depends {
			name: "Qt"
			submodules: [
				"qml",
				"quickcontrols2",
			]
			versionAtLeast: project.minimumQtVersion
		}
		Depends {
			name: "PROGRES"
			submodules: [
				"runtime",
			]
		}
		PROGRES.runtime.qmlPath: project.qmlPath

		name: "progres"
		targetName: "progres"
		version: project.version
		qbs.buildVariant: "release"
		cpp.cxxLanguageVersion: "c++14"
		cpp.treatWarningsAsErrors: true
		cpp.defines: [
			'QT_DEPRECATED_WARNINGS',
			'APPLICATION_NAME="' + project.name + '"',
			'APPLICATION_VERSION="' + project.version + '"',
			'APPLICATION_REPOSITORY="' + project.repository + '"',
		]
		cpp.cxxFlags: [
			"-pedantic-errors",
		]
		cpp.includePaths: [
			"graphics/",
			"gui/",
			"script/",
			"system/",
		]
		FileTagger {
			patterns: "*.hh"
			fileTags: "hpp"
		}

		files: "progres.cc"

		Group {
			name: "graphics"
			prefix: "graphics/"
		}

		Group {
			name: "gui"
			prefix: "gui/"

			Group {
				name: "Source"
				files: ["**/*.cc", "**/*.hh"]
				excludeFiles: [
					"plugins/**",
				]
			}

			Group {
				name: "Resource Data"
				files: [
					"assets/**",
					"qml/**",
				]
				fileTags: "qt.core.resource_data"
				Qt.core.resourceSourceBase: product.sourceDirectory
			}
		}

		Group {
			name: "script"
			prefix: "script/"
		}

		Group {
			name: "system"
			prefix: "system/"
			files: ["**/*.cc", "**/*.hh"]
		}

		Group {
			qbs.install: true
			fileTagsFilter: ["application"]
		}
	}
}
