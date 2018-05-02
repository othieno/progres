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
#include "ResourceImageProvider.hh"
#include "FileInfo.hh"
#include <QQuickStyle>
#include <QQmlContext>

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

	Error (GraphicalUserInterface::* const setups[])() = {
		&GraphicalUserInterface::setupContext,
		&GraphicalUserInterface::setupImageProviders,
		&GraphicalUserInterface::setupServices,
		&GraphicalUserInterface::setupTypes,
	};
	for (auto setup : setups) {
		const Error error = (this->*setup)();
		if (error != Error::None) {
			return error;
		}
	}

	load(QUrl(QStringLiteral("qrc:/ui/qml/main.qml")));
	trimComponentCache();

	return Error::None;
}


Error
GraphicalUserInterface::setupImageProviders()
{
	addImageProvider("resource", new ResourceImageProvider(application_.getResourceManager()));
	return Error::None;
}


Error
GraphicalUserInterface::setupContext()
{
	QQmlContext* const context = rootContext();
	if (context != nullptr) {
		context->setContextProperty("application", &application_);

		return Error::None;
	}
	return Error::NoQmlContext;
}


Error
GraphicalUserInterface::setupTypes()
{
	qmlRegisterUncreatableType<io::File>("File", 1, 0, "File", "Cannot instantiate 'File' class.");

	return Error::None;
}


Error
GraphicalUserInterface::setupServices()
{
	qmlRegisterSingletonType<FileInfo>("Service.FileInfo", 1, 0, "FileInfo", [](QQmlEngine*, QJSEngine*) -> QObject* {
		return new FileInfo;
	});
	return Error::None;
}
