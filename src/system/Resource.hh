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
#ifndef PROGRES_SYSTEM_RESOURCE_HH
#define PROGRES_SYSTEM_RESOURCE_HH

#include <QPixmap>


namespace progres {
namespace system {
/**
 *
 */
class Resource
{
	friend class ResourceManager;
public:
	/**
	 * An enumeration of available resource types.
	 */
	enum class Type
	{
		Pixmap,
		Undefined
	};
	/**
	 *
	 */
	~Resource();
	/**
	 * \fn Type getType() const
	 * \brief Returns the resource's type.
	 */
	Type getType() const;
	/**
	 * \fn bool isValid() const
	 * \brief Returns true if the resource contains recognized data, false otherwise.
	 */
	bool isValid() const;
	/**
	 *
	 */
	const QPixmap* asPixmap() const;
private:
	/**
	 *
	 */
	union Variant
	{
		explicit Variant(const QPixmap* pixmap);
		Variant();

		const QPixmap* const pixmap;
	};

	explicit Resource(const QPixmap* pixmap);
	explicit Resource(std::nullptr_t);

	const Variant variant_;
	const Type type_;
};
} // namespace system
} // namespace progres

#endif // PROGRES_SYSTEM_RESOURCE_HH
