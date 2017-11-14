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
import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item {
	id: item
	anchors.fill: parent

	property string source: ""
	readonly property alias name: project.name

	onSourceChanged: {
		var path = source.trim()
		if (path != project.path) {
			project.close()
			project.load(path)
		}
	}

	QtObject {
		id: project

		property string name: qsTr("Untitled")
		property string path: ""

		function load(path) {
			this.path = path
			console.info("Loading project from", this.path)
		}

		function save() {
			console.info("Saving project to", this.path)
		}

		function close() {
			if (this.path) {
				console.info("Closing project", this.path)
				this.name = qsTr("Untitled")
				this.path = ""
			}
		}
	}

	Flickable {
		id: flickable
		anchors.fill: parent

		clip: true
		interactive: false
		boundsBehavior: Flickable.StopAtBounds
		contentWidth: workspace.width
		contentHeight: workspace.height
		contentX: (contentWidth - width) * 0.5
		contentY: (contentHeight - height) * 0.5
		ScrollBar.vertical: ScrollBar {}
		ScrollBar.horizontal: ScrollBar {}

		Rectangle {
			id: workspace
			anchors.centerIn: parent

			property real scale: 4.0
			readonly property real maxScale: 8.0

			property real zoomLevel: 1.0
			readonly property real maximumZoomLevel: 1.0

			color: Material.background
			clip: true
			width: item.width * maximumZoomLevel
			height: item.height * maximumZoomLevel
			transform: Scale {
				id: scaleTransform
				xScale: workspace.scale
				yScale: workspace.scale
				origin.x: 0.5 * workspace.width
				origin.y: 0.5 * workspace.height
			}

			MouseArea {
				anchors.fill: parent
				hoverEnabled: true
				onWheel: {
/*
					var delta = (0.05 * wheel.angleDelta.y) / 120.0
					workspace.scale = Math.min(Math.max(workspace.scale + delta, 1.0), workspace.maxScale)
					//workspace.zoomLevel = Math.min(Math.max(workspace.zoomLevel + delta, 1.0), workspace.maximumZoomLevel)
					scaleTransform.origin.x = mouseX
					scaleTransform.origin.y = mouseY
					return
					workspace.scaleFactor += 0.05 * wheel.angleDelta.y / 120
					workspace.scaleFactor = Math.min(Math.max(workspace.scaleFactor, min), max)
*/
				}
			}

			DropArea {
				anchors.fill: parent
				onDropped: function(e) {
					if (e.hasUrls) {
						workspace.createVisualScriptNode(e.urls[0], e.x, e.y)
					}
				}
			}
			/**
			 * \fn createVisualScriptNode(source, x, y)
			 * \brief Creates a VisualScriptNode with the specified source, centered at the given <x, y> coordinate.
			 */
			function createVisualScriptNode(source, x, y) {
				var object = Qt.createQmlObject("import VisualScript 1.0; VisualScriptNode {}", workspace)
				if (object) {
					object.source = source || ""
					object.x = x - (0.5 * object.width)
					object.y = y - (0.5 * object.height)
				}
			}
VisualScriptNode {
	id: debugNode
	anchors.centerIn: parent
}
		}
	}

	function initialize() {}
}
