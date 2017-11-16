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
#ifndef PROGRES_GRAPHICAL_USER_INTERFACE_HH
#define PROGRES_GRAPHICAL_USER_INTERFACE_HH

#include <QQmlApplicationEngine>
#include "Error.hh"


namespace progres {
class Application;
/**
 *
 */
class GraphicalUserInterface {
    friend class Application;
public:
    /**
     * \fn GraphicalUserInterface::~GraphicalUserInterface()
     * \brief Destroys the GraphicalUserInterface instance.
     */
    ~GraphicalUserInterface();
    /**
     * \fn void GraphicalUserInterface::getWindow()
     * \brief Returns the application's window instance.
     */
    void getWindow();

    GraphicalUserInterface(const GraphicalUserInterface&) = delete;
    GraphicalUserInterface(GraphicalUserInterface&&) = delete;
    GraphicalUserInterface& operator=(const GraphicalUserInterface&) = delete;
    GraphicalUserInterface& operator=(GraphicalUserInterface&&) = delete;
private:
    /**
     * \fn GraphicalUserInterface::GraphicalUserInterface(Application& application)
     * \brief Instantiates a GraphicalUserInterface object bound to the specified \a application instance.
     */
    explicit GraphicalUserInterface(Application&);
    /**
     * \fn Error GraphicalUserInterface::initialize()
     * \brief Initializes the GraphicalUserInterface instance.
     */
    Error initialize();

    Application& application_;
    QQmlApplicationEngine qmlApplicationEngine_;
};
} // namespace progres

#endif // PROGRES_GRAPHICAL_USER_INTERFACE_HH
