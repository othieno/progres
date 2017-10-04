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
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Rectangle {
    id: workspace

    /**
     * The component's private scope.
     */
    QtObject {
        id: _
        property string name

        /**
         * Creates a VisualScriptNode with the specified source.
         */
        function createVisualScriptNode(source) {
            return Qt.createQmlObject(
                'import VisualScript 1.0; VisualScriptNode {source: "%1"}'.arg(source),
                workspace
            )
        }
    }

    readonly property alias name: _.name

    anchors.fill: parent
    color: Material.color(Material.Grey, Material.Shade900)

    function initialize() {
        _.name = qsTr("Untitled")
    }

    MouseArea {
        anchors.fill: parent
        onClicked: function(e) {
        }
    }

    DropArea {
        anchors.fill: parent
        onDropped: function(e) {
            if (e.hasUrls) {
                var node = _.createVisualScriptNode(e.urls[0])
                if (node != null) {
                    node.x = e.x - (node.width * 0.5)
                    node.y = e.y - (node.height * 0.5)
                }
            }
        }
    }
}
