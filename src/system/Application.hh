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
#include "ApplicationSettings.hh"
#include "GraphicalUserInterface.hh"


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
	Q_PROPERTY(ApplicationSettings* settings READ getSettingsPtr NOTIFY settingsChanged FINAL)
	/**
	 * \property QString Application::repositoryURL
	 * \brief The URL to the application's source code repository.
	 */
	Q_PROPERTY(QString repositoryURL READ getRepositoryURL CONSTANT)
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
	 * \fn QString Application::getRepositoryURL() const
	 * \brief Returns the URL to the project's source code repository.
	 */
	QString getRepositoryURL() const;
private:
	/**
	 * \fn void Application::listResourceFiles()
	 * \brief Lists all resource files associated with this application.
	 */
	void listResourceFiles();

	ApplicationSettings settings_;
	GraphicalUserInterface gui_;
signals:
	/**
	 * \fn void Application::settingsChanged()
	 * \brief A signal that is emitted when the application's settings change.
	 */
	void settingsChanged();
};
} // namespace system
} // namespace progres

#endif // PROGRES_SYSTEM_APPLICATION_HH
