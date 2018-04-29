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
import VisualScript.Controls 1.0 as VisualScriptControls

VisualScriptControls.NodeItem {
	id: pinhole
	/**
	 * The pinhole's diameter.
	 */
	property alias diameter: pinhole.width
	/**
	 * The pinhole's radius.
	 */
	readonly property real radius: 0.5 * diameter
	/**
	 * The mask identifies which pins can be dropped in this pinhole.
	 */
	property int mask
	/**
	 * A label placed next to the pinhole.
	 */
	property alias label: label.text
	/**
	 * The label's font size in pixels.
	 */
	property int labelFontSize: diameter - 2
	/**
	 * The pinhole's color.
	 */
	property var color: "#FFF"
	/**
	 * The pinhole outline's width (thickness).
	 */
	property int outlineWidth: 1
	/**
	 * The pinhole's background color.
	 */
	property alias backgroundColor: circle.color
	/**
	 * The item that is dragged when this pinhole is pressed.
	 */
	property Item dragTarget


	property alias showInnerCircle: innerCircle.visible
	property alias dropEnabled: dropArea.enabled
	property alias dragEnabled: mouseArea.enabled
	property alias keys: dropArea.keys



	/**
	 * A signal that is emitted when a pin is hovering over this pinhole.
	 */
	signal entered(var pin)
	/**
	 * A signal that is emitted when a pin that was hovering over this pinhole exits.
	 */
	signal exited()
	/**
	 * A signal that is raised when the pinhole has been pressed.
	 */
	signal pressed(var mouse)
	/**
	 * A signal that is emitted when a pin is pushed into this pinhole.
	 */
	signal pinned(var pin)
	/**
	 * A signal that is emitted when a pin is removed from the pinhole.
	 */
	signal unpinned()
	/**
	 * A signal that is released when the pin currently being dragged is released.
	 */
	signal released(bool pinned, var mouse)

	width: diameter
	height: diameter

	Rectangle {
		id: circle
		anchors.fill: parent
		radius: width
		border.width: outlineWidth
		border.color: pinhole.color || "#FFF"
		Rectangle {
			id: innerCircle
			anchors.centerIn: parent
			width: parent.width * 0.5
			height: width
			radius: width
			color: pinhole.color
			visible: false
		}
		DropArea {
			id: dropArea
			readonly property var pinhole: parent.parent
			anchors.fill: parent
			onContainsDragChanged: {
				if (containsDrag) {
					pinhole.entered(drag.source);
				} else {
					pinhole.exited();
				}
			}
		}
		MouseArea {
			id: mouseArea
			anchors.fill: parent
			drag {
				target: pinhole.dragTarget
				threshold: 0
			}
			onPressed: pinhole.pressed(mouse)
			onReleased: {
				var pin = drag.target;
				var dropArea = pin.Drag.target;
				var pinned = false;
				if (dropArea) {
					var targetPinhole = dropArea.parent.parent; // The DropArea is contained inside a Rectangle, itself inside a Pinhole.
					if (targetPinhole.mask === pin.mask /* TODO: && !targetPinhole.isLinkedTo(pinhole)*/) {
						targetPinhole.pinned(pin);
						targetPinhole.linkedTo(pinhole);
						pinhole.linkedTo(targetPinhole);
						pinned = pin.mask === pinhole.mask;
					}
				}
				pinhole.released(pinned, mouse);
			}
		}
	}
	Text {
		id: label
		visible: pinhole.label
		text: pinhole.label
		font.pixelSize: pinhole.labelFontSize
		anchors {
			left: pinhole.right
			verticalCenter: parent.verticalCenter
			leftMargin: pinhole.radius
		}
	}
}
