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
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import Fluid.Controls 1.0 as FluidControls

RoundButton {
	id: button

	property alias diameter: button.width

	height: width
	opacity: enabled ? 1.0 : 0.25
	Material.elevation: 1
	background: Rectangle {
		id: background
		anchors.fill: parent
		radius: button.width
		color: button.enabled ? button.Material.background : button.Material.buttonDisabledColor
		FluidControls.Ripple {
			anchors.fill: parent
			control: button
			circular: true
		}
	}
}
