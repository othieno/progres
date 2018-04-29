/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017-2018, Jeremy Othieno. Othieno.
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
#include "GraphicalUserInterface.hh"
#include "Application.hh"
#include <QQuickStyle>

using progres::ui::GraphicalUserInterface;
using progres::system::Application;
using progres::system::Error;


GraphicalUserInterface::GraphicalUserInterface(Application& application) :
application_(application)
{}


Error
GraphicalUserInterface::initialize()
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQuickStyle::setStyle("Material");

	qmlApplicationEngine_.load(QUrl("qrc:/gui/qml/main.qml"));

	return Error::None;
}
