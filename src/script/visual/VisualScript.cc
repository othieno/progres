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
#include "VisualScriptNode.hh"

using visualscript::VisualScript;


VisualScript::VisualScript(QObject* const parent) :
QQmlExtensionPlugin(parent){}


void
VisualScript::registerTypes(const char* uri) {
    Q_ASSERT(uri == QLatin1String("VisualScript"));

    VisualScriptNode::registerType(uri);
}


static void
registerTypes() {
    VisualScriptPlugin visualScriptPlugin;
    visualScriptPlugin.registerTypes("VisualScript");
}
Q_COREAPP_STARTUP_FUNCTION(registerTypes)
