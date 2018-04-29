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
import QtGraphicalEffects 1.0
import Fluid.Controls 1.0 as FluidControls
import "." as UiControls

Item {
	id: carousel

	property int initialIndex: 0
	property bool showPageIndicator: true
	property int radius: 0
	property alias interactive: swipeView.interactive
	default property alias pages: swipeView.contentData
	readonly property alias currentIndex: swipeView.currentIndex
	readonly property int size: swipeView.count
	readonly property bool isLastPage: currentIndex === Math.max(0, size - 1)
	property int navigationButtonDiameter: 48
	property bool enableKeyboardNavigation: true

	Keys.enabled: enableKeyboardNavigation
	Keys.onLeftPressed: swipeView.decrementCurrentIndex()
	Keys.onRightPressed: swipeView.incrementCurrentIndex()

	SwipeView {
		id: swipeView
		anchors.fill: parent
		clip: true
		currentIndex: initialIndex
		layer.enabled: carousel.radius > 0
		layer.effect: OpacityMask {
			maskSource: Rectangle {
				width: carousel.width
				height: carousel.height
				radius: carousel.radius
			}
		}
	}

	PageIndicator {
		id: pageIndicator
		anchors {
			bottom: swipeView.bottom
			horizontalCenter: swipeView.horizontalCenter
			top: swipeView.bottom
			topMargin: 24
		}
		visible: carousel.showPageIndicator && swipeView.count > 1
		count: swipeView.count
		currentIndex: swipeView.currentIndex
	}

	UiControls.RoundButton {
		id: navigationPrevious
		anchors {
			right: carousel.left
			rightMargin: 48
			verticalCenter: carousel.verticalCenter
		}
		visible: swipeView.count > 1
		diameter: navigationButtonDiameter
		enabled: swipeView.currentIndex > 0
		onClicked: {
			swipeView.decrementCurrentIndex();
			carousel.forceActiveFocus();
		}
		icon.color: Qt.darker(Material.background)
		icon.source: FluidControls.Utils.iconUrl("navigation/arrow_back")
	}

	UiControls.RoundButton {
		id: navigationNext
		anchors {
			left: carousel.right
			leftMargin: 48
			verticalCenter: carousel.verticalCenter
		}
		visible: swipeView.count > 1
		diameter: navigationButtonDiameter
		enabled: swipeView.currentIndex < swipeView.count - 1
		onClicked: {
			swipeView.incrementCurrentIndex();
			carousel.forceActiveFocus();
		}
		icon.color: Qt.darker(Material.background)
		icon.source: FluidControls.Utils.iconUrl("navigation/arrow_forward")
	}
	/**
	 * \brief Returns true if a previous page exists, false otherwise.
	 */
	function hasPreviousPage()
	{
		return swipeView.currentIndex > 0;
	}
	/**
	 * \brief Shows the carousel's previous page.
	 */
	function showPreviousPage()
	{
		swipeView.decrementCurrentIndex();
	}
	/**
	 * \brief Returns true if a next page exists, false otherwise.
	 */
	function hasNextPage()
	{
		return swipeView.currentIndex < swipeView.count - 1;
	}
	/**
	 * \brief Shows the carousel's next page.
	 */
	function showNextPage()
	{
		swipeView.incrementCurrentIndex();
	}
}
