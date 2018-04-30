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
import QtQuick.Layouts 1.3
import Fluid.Controls 1.0 as FluidControls
import "../../private" as Private

Private.SettingsView {
	id: view
	title: qsTr("About")

	FluidControls.Subheader {
		text: qsTr("Build information")
	}
	FluidControls.ListItem {
		text: qsTr("Build version")
		subText: "%1 (commit %2)".arg(application.applicationVersion).arg(application.buildCommitHash)
		showDivider: true
	}
	FluidControls.ListItem {
		text: qsTr("Build date")
		subText: application.buildDate.toLocaleString()
		showDivider: true
	}
	FluidControls.ListItem {
		text: qsTr("Source code repository")
		subText: application.repositoryUrl
		rightItem: Button {
			anchors.verticalCenter: parent.verticalCenter
			text: qsTr("Open in browser")
			highlighted: true
			onClicked: Qt.openUrlExternally(application.repositoryUrl)
		}
	}

	FluidControls.Subheader {
		text: qsTr("Legal information")
	}
	FluidControls.ListItem {
		enabled: false
		text: qsTr("Software license")
		subText: qsTr("GPL3+")
		rightItem: FluidControls.Icon {
			anchors.centerIn: parent
			source: FluidControls.Utils.iconUrl("navigation/chevron_right")
			size: FluidControls.Units.iconSizes.small
		}
		showDivider: true
	}
	FluidControls.ListItem {
		enabled: false
		text: qsTr("Documentation license")
		subText: qsTr("Creative Commons (CC BY-NC-SA 4.0)")
		rightItem: FluidControls.Icon {
			anchors.centerIn: parent
			source: FluidControls.Utils.iconUrl("navigation/chevron_right")
			size: FluidControls.Units.iconSizes.small
		}
	}
}
