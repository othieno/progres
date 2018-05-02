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
#ifndef PROGRES_UI_GRAPHICALUSERINTERFACE_HH
#define PROGRES_UI_GRAPHICALUSERINTERFACE_HH

#include <QQmlApplicationEngine>
#include "Error.hh"


namespace progres {
namespace system {
/**
 * \see system/Application.hh.
 */
class Application;
} // namespace system
} // namespace progres

namespace progres {
namespace ui {
/**
 *
 */
class GraphicalUserInterface : private QQmlApplicationEngine
{
	friend class system::Application;
public:
	GraphicalUserInterface(const GraphicalUserInterface&) = delete;
	GraphicalUserInterface(GraphicalUserInterface&&) = delete;
	GraphicalUserInterface& operator=(const GraphicalUserInterface&) = delete;
	GraphicalUserInterface& operator=(GraphicalUserInterface&&) = delete;
	/**
	 * \fn system::Error GraphicalUserInterface::initialize()
	 * \brief Initializes this GraphicalUserInterface instance.
	 */
	system::Error initialize();
	/**
	 * \fn void GraphicalUserInterface::getWindow()
	 * \brief Returns the application's window instance.
	 */
	// void getWindow();
private:
	/**
	 * \fn explicit GraphicalUserInterface::GraphicalUserInterface(system::Application& application)
	 * \brief Instantiates a GraphicalUserInterface object bound to the specified \a application instance.
	 */
	explicit GraphicalUserInterface(system::Application& application);
	/**
	 *
	 */
	system::Error setupImageProviders();
	/**
	 *
	 */
	system::Error setupContext();
	/**
	 *
	 */
	system::Error setupTypes();
	/**
	 *
	 */
	system::Error setupServices();
	/**
	 * \brief A reference to the Application that this user interface is bound to.
	 */
	system::Application& application_;
};
} // namespace ui
} // namespace progres

#endif // PROGRES_UI_GRAPHICALUSERINTERFACE_HH
