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

Item {
	id: pin
	/**
	 * The pin's diameter.
	 */
	property alias diameter: pin.width
	/**
	 * The pin's radius.
	 */
	readonly property real radius: 0.5 * diameter
	/**
	 * The pin's color.
	 */
	property alias color: circle.color
	/**
	 * The mask identifies which pinholes this pin can be dropped into.
	 */
	property int mask

	height: width
	Drag.active: enabled
	Drag.hotSpot.x: 0.5 * width
	Drag.hotSpot.y: 0.5 * height

	Rectangle {
		id: circle
		radius: width
		color: Material.accent
		anchors.fill: parent
		border.color: Qt.rgba(0, 0, 0, 0.1)
	}
}
