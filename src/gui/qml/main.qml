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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0 as FluidControls
import "Pages" as Pages

FluidControls.ApplicationWindow {
	readonly property FluidControls.Page currentPage: pageStack.currentItem

	Material.theme: Material.Light
	Material.primary: Material.color(Material.Blue, Material.Shade500)
	Material.background: Material.color(Material.Grey, Material.Shade300)
	Material.accent: Material.color(Material.LightBlue, Material.ShadeA700)
	visible: true
	visibility: Window.Maximized
	appBar.visible: (currentPage && currentPage.actions.length > 0) || pageStack.depth > 0
	initialPage: Pages.Workspace {}
	title: {
		if (currentPage && currentPage.title) {
			return "%1 - Procedural Graphics Editor Suite".arg(currentPage.title);
		} else {
			return "Procedural Graphics Editor Suite";
		}
	}
}
