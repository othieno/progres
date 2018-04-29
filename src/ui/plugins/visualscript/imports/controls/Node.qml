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

Pane {
	id: node
	/**
	 * The node's name.
	 */
	property string name
	/**
	 * The MouseArea's aliased properties.
	 */
	property alias acceptedButtons: mouseArea.acceptedButtons
	property alias containsMouse: mouseArea.containsMouse
	property alias containsPress: mouseArea.containsPress
	property alias cursorShape: mouseArea.cursorShape
	property alias dragActive: mouseAreaDrag.active
	property alias dragMaximumX: mouseAreaDrag.maximumX
	property alias dragMaximumY: mouseAreaDrag.maximumY
	property alias dragMinimumX: mouseAreaDrag.minimumX
	property alias dragMinimumY: mouseAreaDrag.minimumY
	property alias dragThreshold: mouseAreaDrag.threshold
	property alias dragFilterChildren: mouseAreaDrag.filterChildren
	property alias mouseEventsEnabled: mouseArea.enabled
	property alias mouseX: mouseArea.mouseX
	property alias mouseY: mouseArea.mouseY
	property alias pressAndHoldInterval: mouseArea.pressAndHoldInterval
	property alias pressed: mouseArea.pressed
	property alias pressedButtons: mouseArea.pressedButtons
	property alias preventStealing: mouseArea.preventStealing
	property alias propagateComposedEvents: mouseArea.propagateComposedEvents
	property alias scrollGestureEnabled: mouseArea.scrollGestureEnabled
	/**
	 * The DropArea's aliased properties.
	 */
	property alias containsDrag: dropArea.containsDrag
	property alias dragSource: dropAreaDrag.source
	property alias dragKeys: dropArea.keys
	property alias dropEventsEnabled: dropArea.enabled
	/**
	 *
	 */
	default property alias data: dropArea.data
	/**
	 * Mouse signals.
	 */
	signal mouseClicked(/*MouseEvent*/ var mouse)
	signal mouseDoubleClicked(/*MouseEvent*/ var mouse)
	signal mouseEntered()
	signal mouseEventCanceled()
	signal mouseExited()
	signal mousePositionChanged(/*MouseEvent*/ var mouse)
	signal mousePressAndHold(/*MouseEvent*/ var mouse)
	signal mousePressed(/*MouseEvent*/ var mouse)
	signal mouseReleased(/*MouseEvent*/ var mouse)
	signal mouseWheel(/*WheelEvent*/ var wheel)
	/**
	 * Drag and drop signals.
	 */
	signal dragDropped(/*DragEvent*/ var drop)
	signal dragEntered(/*DragEvent*/ var drag)
	signal dragExited()
	signal dragPositionChanged(/*DragEvent*/ var drag)

	padding: 0
	hoverEnabled: true
	/**
	 *
	 */
	MouseArea {
		id: mouseArea
		anchors.fill: parent
		hoverEnabled: node.hoverEnabled
		drag {
			id: mouseAreaDrag
			target: node
			threshold: 0
			minimumX: 0
			minimumY: 0
			maximumX: node.parent.width - node.width
			maximumY: node.parent.height - node.height
		}
		onPressed: node.mousePressed(mouse)
		Component.onCompleted: {
			canceled.connect(node.mouseEventCanceled);
			clicked.connect(node.mouseClicked);
			doubleClicked.connect(node.mouseDoubleClicked);
			entered.connect(node.mouseEntered);
			exited.connect(node.mouseExited);
			positionChanged.connect(node.mousePositionChanged);
			pressAndHold.connect(node.mousePressAndHold);
			released.connect(node.mouseReleased);
			wheel.connect(node.mouseWheel);
		}
	}
	/**
	 *
	 */
	DropArea {
		id: dropArea
		anchors.fill: parent
		drag {
			id: dropAreaDrag
		}
		Component.onCompleted: {
			dropped.connect(node.dragDropped);
			entered.connect(node.dragEntered);
			exited.connect(node.dragExited);
			positionChanged.connect(node.dragPositionChanged);
		}
	}
	/**
	 * A special property used by NodeComponents to find the node they are attached to.
	 */
	readonly property bool __VISUALSCRIPT_NODE__: true
}
