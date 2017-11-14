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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.6
import VisualScript 1.0

VisualScriptNodeBase {
    width: 48
    height: 24

    Rectangle {
        id: preview
        anchors.fill: parent
        color: "#999"
        Text {
            anchors.centerIn: parent
            font.pixelSize: 4
            text: parent.state
        }

        states: [
            State {
                name: "Unspecified"
                when: type == VisualScriptNodeType.Unspecified
                PropertyChanges {}
            },
            State {
                name: "Image"
                when: type == VisualScriptNodeType.Image
                PropertyChanges {}
            },
            State {
                name: "Audio"
                when: type == VisualScriptNodeType.Audio
                PropertyChanges {}            },
            State {
                name: "Video"
                when: type == VisualScriptNodeType.Video
            },
            State {
                name: "Source Code"
                when: type == VisualScriptNodeType.SourceCode
                PropertyChanges {}
            }
        ]
    }
}
