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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Application.hh"
#include "GraphicalUserInterface.hh"
#include <QDirIterator>
#include <QDebug>

using progres::system::Application;
using progres::system::ApplicationSettings;
using progres::system::Error;


Application::Application(int& argc, char** argv) :
QGuiApplication(argc, argv),
gui_(*this)
{
	setApplicationName(APPLICATION_NAME);
	setApplicationVersion(APPLICATION_VERSION);
	connect(&settings_, &ApplicationSettings::valueChanged, this, &Application::settingsChanged);
}


Application::~Application()
{}


ApplicationSettings&
Application::getSettings()
{
	return settings_;
}


const ApplicationSettings&
Application::getSettings() const
{
	return settings_;
}


ApplicationSettings*
Application::getSettingsPtr()
{
	return &settings_;
}


QString
Application::getRepositoryURL() const
{
	return QString(APPLICATION_REPOSITORY);
}


Error
Application::initialize()
{
	//const auto& arguments = QApplication::arguments();
	Error error = gui_.initialize();
	if (error != Error::None) {
		return error;
	}

	// TODO Initialize other compponents.

#ifdef QT_DEBUG
	listResourceFiles();
#endif
	return Error::None;
}


void
Application::listResourceFiles()
{
	QDirIterator it(":", QDirIterator::Subdirectories);
	while (it.hasNext()) {
		qInfo() << it.next();
	}
}
