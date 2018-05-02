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
#include "File.hh"
#include <QMimeDatabase>
#include <QDirIterator>
#include <QDebug>

using progres::io::File;


File::Type
File::getType() const
{
	return type_;
}


QMimeType
File::getMimeType(const QUrl& url)
{
	return QMimeDatabase().mimeTypeForUrl(url);
}


File::Type
File::getType(const QUrl& url, QByteArray* const subtypeName)
{
	const auto mimeTypeName = getMimeType(url).name().split("/");
	if (subtypeName != nullptr) {
		*subtypeName = mimeTypeName[1].toLatin1();
	}

	const auto& typeName = mimeTypeName[0];
	if (typeName == "audio") {
		return Type::Audio;
	} else if (typeName == "image") {
		return Type::Image;
	} else if (typeName == "text") {
		return Type::Text;
	} else if (typeName == "video") {
		return Type::Video;
	} else if (typeName == "multipart") {
		return Type::Multipart;
	}
	return Type::Application;
}


QByteArray
File::getTypeName(const Type type)
{
	switch (type) {
		case Type::Audio:
			return "Audio";
		case Type::Image:
			return "Image";
		case Type::Text:
			return "Text";
		case Type::Video:
			return "Video";
		case Type::Multipart:
			return "Multipart";
		case Type::Application:
			return "Application";
	}
	qFatal("[File::getTypeName] Unknown file type!");
}


void
File::listResourceFiles()
{
	QDirIterator it(":", QDirIterator::Subdirectories);
	while (it.hasNext()) {
		qInfo() << it.next();
	}
}
