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

Project {
	property string qmlPath: "/qml"

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
		Depends {name: "visualscript"}
		Depends {name: "vcs"; headerFileName: undefined}
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
		cpp.cxxFlags: [
			"-pedantic-errors",
		]
		cpp.cxxLanguageVersion: "c++14"
		cpp.defines: [
			'QT_DEPRECATED_WARNINGS',
			'APPLICATION_BUILD_DATE=' + Date.now(),
			'APPLICATION_BUILD_COMMIT_HASH="' + vcs.repoState + '"',
			'APPLICATION_NAME="' + project.shortName + '"',
			'APPLICATION_ORGANIZATION_DOMAIN="' + project.organizationDomain + '"',
			'APPLICATION_ORGANIZATION_NAME="' + project.organizationName + '"',
			'APPLICATION_REPOSITORY_URL="' + project.repositoryUrl + '"',
			'APPLICATION_VERSION="' + project.version + '"',
		]
		cpp.includePaths: [
			"graphics/",
			"gui/",
			"script/",
			"system/",
		]
		cpp.treatWarningsAsErrors: true
		qbs.buildVariant: "release"

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
