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
#ifndef VISUALSCRIPT_PLUGIN_HH
#define VISUALSCRIPT_PLUGIN_HH

#include <QQmlExtensionPlugin>


namespace visualscript {
/**
 *
 */
class Plugin : public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
	void initializeEngine(QQmlEngine* const engine, const char* const uri) override;
	void registerTypes(const char* const uri) override;
};
} // namespace visualscript

using VisualScriptPlugin = visualscript::Plugin;

#endif // VISUALSCRIPT_PLUGIN_HH
