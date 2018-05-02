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
#ifndef PROGRES_IO_FILE_HH
#define PROGRES_IO_FILE_HH

#include <QFile>
#include <QMimeType>


namespace progres {
namespace io {
/**
 *
 */
class File : public QFile
{
	Q_OBJECT
public:
	/**
	 * An enumeration of recognized file types.
	 */
	enum class Type : int
	{
		Audio,
		Image,
		Text,
		Video,
		Multipart,
		Application
	};
	Q_ENUM(Type)
	/**
	 * Returns the file's type.
	 */
	Type getType() const;
	/**
	 * \fn static QMimeType getMimeType(const QUrl& url)
	 * \brief Returns the MIME type of the file located at the specified URL.
	 */
	static QMimeType getMimeType(const QUrl& url);
	/**
	 * \fn static Type getType(const QUrl& url, QByteArray* const subtypeName = nullptr)
	 * \brief Returns the type of the file located at the specified URL.
	 */
	static Type getType(const QUrl& url, QByteArray* const subtypeName = nullptr);
	/**
	 * \fn QByteArray getTypeName(const Type type)
	 * \brief Returns the specified type's name as a human-readable string.
	 */
	static QByteArray getTypeName(const Type type);
	/**
	 * \fn static void listResourceFiles()
	 * \brief Prints a list of all available resource files.
	 */
	static void listResourceFiles();
private:
	/**
	 * The file's type.
	 */
	Type type_;
};
} // namespace io
} // namespace progres

#endif // PROGRES_IO_FILE_HH
