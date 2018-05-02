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
#include "FileInfo.hh"

using progres::ui::FileInfo;
using progres::io::File;


FileInfo::FileInfo(QObject* const parent) :
QObject(parent)
{}


int
FileInfo::type(const QUrl& url) const
{
	return static_cast<int>(File::getType(url));
}


QByteArray
FileInfo::typeName(const int type) const
{
	return File::getTypeName(static_cast<File::Type>(type));
}


QByteArray
FileInfo::mimeType(const QUrl& url) const
{
	return File::getMimeType(url).name().toLatin1();
}
