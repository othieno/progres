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
import VisualScript.Controls 1.0 as VisualScriptControls

VisualScriptControls.Pinhole {
	id: pinhole
	/**
	 *
	 */
	enum Direction {
		In,
		Out
	}
	/**
	 * The pinhole's data direction.
	 */
	property int direction: Pinhole.Direction.In


	signal linkedTo(var pinhole)

	keys: ReusablePin.Drag.keys
	dragTarget: ReusablePin
	dragEnabled: direction === Pinhole.Direction.Out
	dropEnabled: direction === Pinhole.Direction.In
	onEntered: outlineWidth = pin.mask === pinhole.mask ? 3 : 1
	onExited: outlineWidth = 1
	onPressed: {
		ReusablePin.origin = pinhole;
		ReusablePin.resetPosition();
		ReusablePin.visible = true;
		ReusableWire.origin = pinhole;
		ReusableWire.visible = true;
	}
	onPinned: {
		link(pin.origin);
		showInnerCircle = true;
	}
	onUnpinned: {
		showInnerCircle = false;
	}
	onReleased: {
		ReusablePin.visible = false;
		ReusableWire.visible = false;
	}
	/**
	 * A component that makes it easier for the link function to create
	 * wires starting at this pinhole's center and ending at another item's center.
	 */
	Component {
		id: wireComponent
		Wire {
			readonly property var start: pinhole
			property var end
			color: start.color
			startX: start.absoluteX + start.radius
			startY: start.absoluteY + start.radius
			endX: end.absoluteX + end.radius
			endY: end.absoluteY + end.radius
		}
	}
	/**
	 * \fn link(to)
	 * \brief Links this pinhole to another.
	 */
	function link(to)
	{
		return wireComponent.createObject(workspace, {end: to});
	}
}
