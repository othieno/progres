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
import QtQuick.Layouts 1.0
import Fluid.Controls 1.0 as FluidControls
import "../Controls" as UiControls
import "private" as Private

Private.Page {
	id: page
	showAppBar: workspaceView.active
	title: workspaceView.name
	actions: [
		FluidControls.Action {
			text: qsTr("Notifications")
			icon.source: FluidControls.Utils.iconUrl("social/notifications")
			// icon.color: Material.color(Material.Amber, Material.Shade500)
			visible: false
			enabled: !settingsLoader.active
		},
		FluidControls.Action {
			text: qsTr("Save workspace")
			toolTip: qsTr("Save the current workspace")
			icon.source: FluidControls.Utils.iconUrl("content/save")
			enabled: !settingsLoader.active && workspaceView.active
			// enabled: !workspaceView.saving
			visible: !workspaceView.empty
			// onTriggered: workspaceView.save()
		},
		FluidControls.Action {
			text: qsTr("User manual")
			toolTip: qsTr("Read the user manual")
			icon.source: FluidControls.Utils.iconUrl("action/class")
			enabled: !settingsLoader.active
			onTriggered: pageStack.push("qrc:/ui/qml/Pages/UserManual.qml")
		},
		FluidControls.Action {
			text: qsTr("Application Settings")
			icon.source: FluidControls.Utils.iconUrl("action/settings")
			hoverAnimation: !settingsLoader.active
			onTriggered: settingsLoader.active = !settingsLoader.active
		}
	]

	Private.Introduction {
		id: introduction
		anchors.centerIn: parent
		width: 640
		height: 512
		Component.onDestruction: workspaceView.active = true;
	}

	UiControls.WorkspaceView {
		id: workspaceView
		anchors.fill: parent
		enabled: active && !settingsLoader.active
	}

	Loader {
		id: settingsLoader
		anchors {
			top: parent.top
			left: parent.horizontalCenter
			right: parent.right
			bottom: parent.bottom
			margins: FluidControls.Units.smallSpacing * 2
			leftMargin: 0
		}
		active: false
		sourceComponent: FluidControls.Card {
			Settings {
				anchors.fill: parent
			}
		}
	}
}
