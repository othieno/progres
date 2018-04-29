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
import "../../Controls" as UiControls

Item {
	id: onboarding
	focus: true
	Keys.forwardTo: carousel

	UiControls.Carousel {
		id: carousel

		property var messages: [
			{
				"illustration": null,
				"caption": qsTr("Create and edit graphics in real-time"),
				"subcaption": qsTr("Call your momma in the room and show her how great you are")
			},
			{
				"illustration": null,
				"caption": qsTr("Create and edit graphics in real-time"),
				"subcaption": qsTr("Call your momma in the room and show her how great you are")
			},
		]

		anchors.fill: parent
		radius: 8
		Repeater {
			model: carousel.messages
			Loader {
				active: SwipeView.isPreviousItem || SwipeView.isCurrentItem || SwipeView.isNextItem
				sourceComponent: Rectangle {
					anchors.fill: parent
					color: Material.primary
					Image {
						anchors.centerIn: parent
						// source: modelData.illustration
						fillMode: Image.PreserveAspectCrop
						asynchronous: true
					}
					FluidControls.TitleLabel {
						anchors.bottom: bottomPadding.top
						anchors.bottomMargin: 28
						anchors.horizontalCenter: parent.horizontalCenter
						text: modelData.caption
						color: Material.background
					}
					FluidControls.SubheadingLabel {
						anchors.bottom: bottomPadding.top
						anchors.bottomMargin: 0
						anchors.horizontalCenter: parent.horizontalCenter
						text: modelData.subcaption
						color: Material.background
					}
					Rectangle {
						id: bottomPadding
						anchors {
							bottom: parent.bottom
						}
						color: "transparent"
						width: parent.width
						height: start.height + start.anchors.bottomMargin + 28
					}
				}
			}
		}
	}

	Button {
		id: start
		anchors {
			bottom: carousel.bottom
			bottomMargin: 24
			horizontalCenter: carousel.horizontalCenter
		}
		text: qsTr("Get started")
		onClicked: {
			fadeAnimation.from = 1;
			fadeAnimation.to = 0;
			fadeAnimation.runningChanged.connect(function(running){
				if (!running) {
					onboarding.enabled = false;
				}
			});
			fadeAnimation.start();
		}
	}

	NumberAnimation on opacity {
		id: fadeAnimation
		from: 0
		to: 1
		duration: 300
	}
}
