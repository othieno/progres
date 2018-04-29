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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "VisualScriptControlsPlugin.hh"
#include "NodeItem.hh"
#include "Wire.hh"

using visualscript::controls::Plugin;


void
Plugin::initializeEngine(QQmlEngine* const engine, const char* const uri)
{
	Q_ASSERT(engine != nullptr);
	Q_ASSERT(uri == QByteArray(PLUGIN_URI));
}


void
Plugin::registerTypes(const char* const uri)
{
	Q_ASSERT(uri == QByteArray(PLUGIN_URI));

	qmlRegisterType<NodeItem>(uri, 1, 0, "NodeItem");
	qmlRegisterType<Wire>(uri, 1, 0, "Wire");
}
