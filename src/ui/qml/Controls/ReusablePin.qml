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
VisualScriptControls.Pin {
	id: pin
	/**
	 * The pinhole from which this pin originated.
	 */
	property Pinhole origin

	parent: null
	z: 2097152
	visible: false
	Drag.keys: "Controls.Pin"
	onOriginChanged: {
		if (origin) {
			diameter = origin.diameter * 0.75;
			mask = origin.mask;
			color = origin.color;
		} else {
			diameter = 0;
			mask = 0;
			color = "#FFF";
		}
	}
	/**
	 * \fn resetPosition()
	 * \brief Sets the pin's position to the origin's center.
	 */
	function resetPosition()
	{
		if (origin) {
			x = origin.absoluteX + (origin.radius - pin.radius);
			y = origin.absoluteY + (origin.radius - pin.radius);
		} else {
			x = 0;
			y = 0;
		}
	}
}
