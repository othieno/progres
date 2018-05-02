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
#ifndef PROGRES_UI_SERVICES_FILEINFO_HH
#define PROGRES_UI_SERVICES_FILEINFO_HH

#include "File.hh"


namespace progres {
namespace ui {
/**
 *
 */
class FileInfo : public QObject
{
	Q_OBJECT
	friend class GraphicalUserInterface;
public:
	// The FileInfo class' member functions assume the File::Type enumeration's underlying
	// type is an integer; trust but verify.
	Q_STATIC_ASSERT((std::is_same<int, std::underlying_type_t<io::File::Type>>::value));
	/**
	 * \fn int type(const QUrl& url) const
	 * \brief Returns the type of the file located at the specified URL.
	 */
	Q_INVOKABLE int type(const QUrl& url) const;
	/**
	 * \fn QByteArray typeName(const int type) const
	 * \brief Returns the specified type's human-readable name.
	 */
	Q_INVOKABLE QByteArray typeName(const int type) const;
	/**
	 * \fn QByteArray mimeType(const QUrl& url) const
	 * \brief Returns the MIME type of the file located at the specified URL.
	 */
	Q_INVOKABLE QByteArray mimeType(const QUrl& url) const;
private:
	explicit FileInfo(QObject* const parent = nullptr);
	Q_DISABLE_COPY(FileInfo)
};
} // namespace ui
} // namespace progres

#endif // PROGRES_UI_SERVICES_FILEINFO_HH
