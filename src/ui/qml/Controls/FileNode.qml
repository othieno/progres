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
import QtQuick 2.10
import QtQuick.Controls.Material 2.3
import Fluid.Controls 1.0 as FluidControls

Node {
	id: node
	type: Node.Type.File
	/**
	 *
	 */
	QtObject {
		id: internal
		/**
		 * The current file's resource identifier.
		 */
		property string resourceId
	}
	/**
	 * The path to the file.
	 */
	property string filename

	width: 160
	height: 80
	onFilenameChanged: {
		if (internal.resourceId) {
			application.resources.remove(internal.resourceId);
		}
		internal.resourceId = application.resources.add(filename);
	}

	Rectangle {
		anchors.fill: parent
		color: Qt.darker(Material.background)
		clip: true
		FluidControls.Icon {
			anchors.centerIn: parent
			visible: previewer.status !== Image.Ready
			source: FluidControls.Utils.iconUrl("image/landscape")
			size: FluidControls.Units.iconSizes.huge
			color: Qt.lighter(parent.color)
		}
		Image {
			id: previewer
			anchors.centerIn: parent
			asynchronous: true
			cache: true
			source: "image://resource/%0".arg(internal.resourceId)
			sourceSize.width: node.width
			sourceSize.height: node.height
		}
	}

	Pinhole {
		id: pinhole
/*
	readonly property var colors: [
		Material.Grey,
		Material.Indigo,
		Material.LightBlue,
		Material.Lime,
		Material.Purple,
		Material.DeepOrange,
	]
	readonly property var color: Material.color(colors[Math.max(0, acceptedMatchId % colors.length)], Material.Shade700)
*/
		anchors {
			right: parent.right
			verticalCenter: parent.verticalCenter
			rightMargin: pinhole.radius
		}
		color: Material.accent
		visible: internal.resourceId.length > 0
		// mask: node.valueType
		diameter: parent.height * 0.15
		direction: Pinhole.Direction.Out
		// visible: node.value !== undefined
	}
}
