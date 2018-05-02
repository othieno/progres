/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017-2018, Jeremy Othieno. Othieno.
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
import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Fluid.Controls 1.0 as FluidControls

Item {
	id: workspace

	property string name
	readonly property var viewport: parent
	readonly property bool empty: data.length > 0
	default property alias data: body.data

	signal fileDropped(string filename, real x, real y)
	signal nodeAdded(Node node)

	Flickable {
		anchors.fill: parent
		contentWidth: viewport.width * body.scale
		contentHeight: viewport.height * body.scale
		contentX: (contentWidth - width) * 0.5
		contentY: (contentHeight - height) * 0.5
		clip: true
		pixelAligned: true
		boundsBehavior: Flickable.StopAtBounds
		focus: true
		ScrollBar.vertical: ScrollBar {}
		ScrollBar.horizontal: ScrollBar {}
		Keys.onPressed: {
			switch (event.key) {
				case Qt.Key_Plus:
					zoom(1);
					break;
				case Qt.Key_Minus:
					zoom(-1);
					break;
				default:
					break;
			}
		}
		/**
		 *
		 */
		DropArea {
			id: body

			readonly property int scaleMin: 1
			readonly property int scaleMax: 7
			readonly property int scaleStep: 2

			anchors.centerIn: parent
			// scale: scaleMax
			width: viewport.width * scale
			height: viewport.height * scale
			clip: true
			onDropped: function(drop) {
				if (drop.hasUrls) {
					workspace.fileDropped(drop.urls[0], drop.x, drop.y);
				}
			}
		}
/*
		MouseArea {
			anchors.fill: parent
			enabled: !interactive && !mouseEventThrottle.running
			onWheel: {
				workspace.zoom(workspace.scaleStep * Math.sign(wheel.angleDelta.y));
				mouseEventThrottle.start();
			}
			Timer {
				id: mouseEventThrottle
				interval: 450
			}
		}
*/
	}
	/**
	 * \fn zoom(step)
	 * \brief Enlargens or shrinks the workspace based on the specified direction.
	 */
	function zoom(direction)
	{
		transformOrigin.x = x;
		transformOrigin.y = y;
		body.scale = Math.min(Math.max(body.scale + direction * body.scaleStep, body.scaleMin), body.scaleMax);
		//workspace.zoomLevel = Math.min(Math.max(workspace.zoomLevel + delta, 1.0), workspace.maximumZoomLevel)
		// scaleTransform.origin.x = mouseX
		// scaleTransform.origin.y = mouseY
/*
		Rectangle {
			// transform: Scale {
			// 	id: scaleTransform
			// 	xScale: workspace.scale
			// 	yScale: workspace.scale
			// 	origin.x: 0.5 * workspace.width
			// 	origin.y: 0.5 * workspace.height
			// }
		}
*/
	}
	/**
	 * \fn createNode(nodeComponent, properties)
	 * \brief Creates an instance of the specified node component, with the given properties.
	 */
	function createNode(nodeComponent, properties)
	{
		var node = nodeComponent ? nodeComponent.createObject(body, properties) : null;
		if (node) {
			workspace.nodeAdded(node);
		}
		return node;
	}
	/**
	 * \fn addNode(node)
	 * \brief Adds the specified node to the workspace.
	 */
	function addNode(node)
	{
		if (node) {
			node.parent = body;
			workspace.nodeAdded(node);
		}
	}
}
