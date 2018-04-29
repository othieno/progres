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

using progres::system::Application;
using progres::system::ApplicationSettings;
using progres::system::ResourceManager;
using progres::system::Error;


Application::Application(int& argc, char** argv) :
QGuiApplication(argc, argv),
resourceManager_(*this),
gui_(*this)
{
	setApplicationName(QStringLiteral(APPLICATION_NAME));
	setApplicationVersion(QStringLiteral(APPLICATION_VERSION));
	setOrganizationName(QStringLiteral(APPLICATION_ORGANIZATION_NAME));
	setOrganizationDomain(QStringLiteral(APPLICATION_ORGANIZATION_DOMAIN));
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


ResourceManager&
Application::getResourceManager()
{
	return resourceManager_;
}


const ResourceManager&
Application::getResourceManager() const
{
	return resourceManager_;
}


ResourceManager*
Application::getResourceManagerPtr()
{
	return &resourceManager_;
}


QDateTime
Application::getBuildDate()
{
	return QDateTime::fromMSecsSinceEpoch(APPLICATION_BUILD_DATE);
}


QString
Application::getBuildCommitHash()
{
	return QStringLiteral(APPLICATION_BUILD_COMMIT_HASH);
}


QString
Application::getRepositoryUrl()
{
	return QStringLiteral(APPLICATION_REPOSITORY_URL);
}


Error
Application::initialize()
{
	//const auto& arguments = QGuiApplication::arguments();
	Error error;

	// TODO Initialize other compponents.

	error = gui_.initialize();
	if (error != Error::None) {
		return error;
	}
	return Error::None;
}
