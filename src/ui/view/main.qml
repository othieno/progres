/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017, Jeremy Othieno.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0
import VisualScript 1.0

ApplicationWindow {
    Material.theme: Material.Light
    Material.primary: Material.color(Material.Blue, Material.Shade500)
    Material.background: Material.color(Material.Grey, Material.Shade300)
    Material.accent: Material.color(Material.LightBlue, Material.ShadeA700)

    id: applicationWindow
    title: "%1Procedural Graphics Editor Suite".arg(initialPage.title ? initialPage.title + " - " : "")
    visible: true
    visibility: Window.Maximized
    appBar.visible: false
    initialPage: Page {
        title: workspace.visible && workspace.name ? workspace.name : ""
        actions: [
            Action {
                text: qsTr("Application Settings")
                toolTip: qsTr("Configure the application's settings")
                onTriggered: pageStack.push("qrc:/view/settings/main.qml")
                hoverAnimation: true
            }
        ]

        Quickstart {
            id: quickstart
            anchors.fill: parent
            visible: true
            onStarted: {
                visible = false
                appBar.visible = true
                workspace.parent.openWave(0, 0)
            }
        }

        Wave {
            anchors.fill: parent
            onFinished: workspace.initialize()
            VisualScriptWorkspace {
                id: workspace
                visible: !quickstart.visible
            }
        }
    }
}
