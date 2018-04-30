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
pragma Singleton
import QtQuick 2.10
import VisualScript.Controls 1.0 as VisualScriptControls

/**
 *
 */
Wire {
	// An item that the wire's starting point is tethered to.
	// The item is assumed to be a VisualScript.Item object.
	property var origin

	parent: null
	z: -2097151 // Place this wire above all other wires.
	visible: false
	startX: origin ? origin.absoluteX + origin.radius : 0
	startY: origin ? origin.absoluteY + origin.radius : 0
	endX: ReusablePin.x + ReusablePin.radius
	endY: ReusablePin.y + ReusablePin.radius
	color: ReusablePin.color
}
