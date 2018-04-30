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
import "private" as Private

Private.Page {
	id: page
	header: ToolBar {
		Material.elevation: 0
		Material.background: Material.color(Material.BlueGrey, Material.Shade100)
		Item {
			anchors.fill: parent
			anchors.rightMargin: anchors.leftMargin
			FluidControls.ToolButton {
				visible: stackView.depth > 1
				icon.source: FluidControls.Utils.iconUrl("navigation/arrow_back")
				icon.color: Qt.darker(Material.background)
				onClicked: stackView.pop()
			}
			FluidControls.TitleLabel {
				anchors.centerIn: parent
				text: stackView.currentItem.title
				color: Qt.darker(Material.background)
			}
		}
	}
	footer: ToolBar {
		Material.elevation: header.Material.elevation
		Material.background: header.Material.background
		FluidControls.ListItem {
			enabled: false
			text: qsTr("Configuration file location")
			// valueText: application.settings.filename
			Component.onCompleted: valueText = application.settings.filename // Not doing it this way makes QML complain about the use of non-NOTIFYABLE properties...
		}
	}

	StackView {
		id: stackView
		anchors.fill: parent
		clip: true
		initialItem: Private.SettingsView {
			id: listView
			title: qsTr("Settings")
			Repeater {
				model: ListModel {
					id: settingsListModel
					ListElement {
						text: qsTr("Language")
						subText: qsTr("Choose your preferred language")
						iconName: "action/translate"
						page: "qrc:/ui/qml/Pages/views/settings/Language.qml"
					}
					ListElement {
						text: qsTr("Theme")
						subText: qsTr("Change the way the application looks")
						iconName: "image/palette"
						page: "qrc:/ui/qml/Pages/views/settings/Theme.qml"
					}
					ListElement {
						text: qsTr("Notifications")
						subText: qsTr("Manage notification preferences")
						iconName: "social/notifications"
						page: "qrc:/ui/qml/Pages/views/settings/Notifications.qml"
					}
					ListElement {
						text: qsTr("About")
						subText: qsTr("Get more information about the current build")
						iconName: "action/info_outline"
						page: "qrc:/ui/qml/Pages/views/settings/About.qml"
					}
				}
				delegate: FluidControls.ListItem {
					text: model.text
					subText: model.subText
					leftItem: FluidControls.Icon {
						anchors.centerIn: parent
						source: FluidControls.Utils.iconUrl(model.iconName)
						size: FluidControls.Units.iconSizes.medium
					}
					rightItem: FluidControls.Icon {
						anchors.centerIn: parent
						source: FluidControls.Utils.iconUrl("navigation/chevron_right")
						size: FluidControls.Units.iconSizes.small
					}
					onClicked: stackView.push(model.page)
					showDivider: model.index !== settingsListModel.count - 1
					dividerInset: 0
				}
			}
		}
	}
}
