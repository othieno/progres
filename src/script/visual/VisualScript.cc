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
#include "VisualScript.hh"
#include "VisualScriptItem.hh"
#include "VisualScriptNode.hh"
#include "VisualScriptWire.hh"

using visualscript::VisualScript;


VisualScript::VisualScript(QObject* const parent) :
QQmlExtensionPlugin(parent) {}


void
VisualScript::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String(VisualScript::URI));

    qmlRegisterType<Item>(uri, 1, 0, "VisualScriptItem");
    qRegisterMetaType<Item*>("Item*");

    qmlRegisterType<VisualScriptNodeBase>(uri, 1, 0, "VisualScriptNodeBase");
    qmlRegisterType<Wire>(uri, 1, 0, "VisualScriptWire");
    qRegisterMetaType<Wire*>("Wire*");
}


void
VisualScript::initialize(QQmlEngine& engine)
{
    VisualScript plugin;
    plugin.initializeEngine(&engine, VisualScript::URI);
    plugin.registerTypes(VisualScript::URI);
}
