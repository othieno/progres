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
#ifndef PROGRES_SYSTEM_APPLICATION_HH
#define PROGRES_SYSTEM_APPLICATION_HH

#include <QGuiApplication>
#include <QDateTime>
#include "ApplicationSettings.hh"
#include "GraphicalUserInterface.hh"
#include "ResourceManager.hh"


namespace progres {
namespace system {
/**
 *
 *
 */
class Application : public QGuiApplication
{
	Q_OBJECT
	/**
	 * \property ApplicationSettings Application::settings
	 * \brief The application's configuration.
	 */
	Q_PROPERTY(ApplicationSettings* settings READ getSettingsPtr FINAL)
	/**
	 * \property ResourceManager* Application::resources
	 * \brief The application's resource manager.
	 */
	Q_PROPERTY(ResourceManager* resources READ getResourceManagerPtr FINAL)
	/**
	 * \property QDateTime Application::buildDate
	 * \brief The time at the moment this application was built.
	 */
	Q_PROPERTY(QDateTime buildDate READ getBuildDate CONSTANT)
	/**
	 * \property QString Application::buildCommitHash
	 * \brief The hash of the commit that the application was built from.
	 */
	Q_PROPERTY(QString buildCommitHash READ getBuildCommitHash CONSTANT)
	/**
	 * \property QString Application::repositoryUrl
	 * \brief The URL to the application's source code repository.
	 */
	Q_PROPERTY(QString repositoryUrl READ getRepositoryUrl CONSTANT)
public:
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;
	/**
	 * \fn Application::Application(int& argc, char** argv)
	 * \brief Instantiates an Application object.
	 */
	Application(int& argc, char** argv);
	/**
	 * \fn Application::~Application()
	 * \brief Destroys the Application instance.
	 */
	~Application();
	/**
	 * \fn Error Application::initialize()
	 * \brief Initializes the Application instance.
	 */
	Error initialize();
	/**
	 * \fn ApplicationSettings& Application::getSettings()
	 * \brief Returns a reference to the application's settings.
	 */
	ApplicationSettings& getSettings();
	/**
	 * \fn const ApplicationSettings& Application::getSettings() const
	 * \brief Returns a const-reference to the application's settings.
	 */
	const ApplicationSettings& getSettings() const;
	/**
	 * \fn ApplicationSettings* Application::getSettingsPtr()
	 * \brief Returns a pointer to the application's settings.
	 */
	ApplicationSettings* getSettingsPtr();
	/**
	 * \fn ResourceManager& Application::getResourceManager()
	 * \brief Returns a reference to the application's resource manager.
	 */
	ResourceManager& getResourceManager();
	/**
	 * \fn const ResourceManager& Application::getResourceManager() const
	 * \brief Returns a const reference to the application's resource manager.
	 */
	const ResourceManager& getResourceManager() const;
	/**
	 * \fn ResourceManager* getResourceManagerPtr()
	 * \brief Returns a pointer to the application's resource manager.
	 */
	ResourceManager* getResourceManagerPtr();
	/**
	 * \fn static QDateTime Application::getBuildDate()
	 * \brief Returns the UNIX time at the moment this application was built.
	 */
	static QDateTime getBuildDate();
	/**
	 * \fn static QString Application::getBuildCommitHash()
	 * \brief Returns the hash of the commit that the application was built from.
	 */
	static QString getBuildCommitHash();
	/**
	 * \fn static QString Application::getRepositoryUrl()
	 * \brief Returns the URL to the project's source code repository.
	 */
	static QString getRepositoryUrl();
private:
	ApplicationSettings settings_;
	ResourceManager resourceManager_;
	ui::GraphicalUserInterface gui_;
};
} // namespace system
} // namespace progres

#endif // PROGRES_SYSTEM_APPLICATION_HH
