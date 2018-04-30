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
	id: introduction
	Component.onCompleted: countdownTimer.start()

	Timer {
		id: countdownTimer
		interval: 2000
		onTriggered: fadeOutAnimation.start()
	}

	Rectangle {
		anchors.fill: parent
		color: "transparent"

		FontLoader {
			id: fontLoader
			source: "qrc:/ui/assets/fonts/Montserrat-ExtraBold.ttf"
		}

		Text {
			anchors {
				verticalCenter: parent.verticalCenter
				left: parent.left
				leftMargin: 11
			}
			font {
				family: fontLoader.name
				pixelSize: 82
				letterSpacing: 32
			}
			style: Text.Outline
			opacity: 0.75
			color: Material.shade(Material.background, Material.Shade800)
			styleColor: Material.shade(Material.background, Material.Shade900)
			text: application.applicationName
		}

		NumberAnimation on opacity {
			id: fadeOutAnimation
			to: 0
			running: false
			duration: 300
			onRunningChanged: {
				if (!running) {
					if (application.settings.onboardingEnabled) {
						onboardingLoader.active = true;
					} else {
						introduction.destroy();
					}
				}
			}
		}
	}

	Loader {
		id: onboardingLoader
		anchors.centerIn: parent
		active: false
		focus: active
		sourceComponent: Onboarding {
			id: onboarding
			width: 640
			height: 512
			opacity: 0
			onEnabledChanged: {
				if (!enabled) {
					application.settings.onboardingEnabled = false;
					introduction.destroy();
				}
			}
		}
	}
}
