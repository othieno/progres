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
#include "Resource.hh"

using progres::system::Resource;


Resource::Resource(std::nullptr_t) :
variant_(),
type_(Type::Undefined)
{}


Resource::Resource(const QPixmap* image) :
variant_(image),
type_(Type::Pixmap)
{}


Resource::~Resource()
{
	//TODO
}


Resource::Type
Resource::getType() const
{
	return type_;
}


bool
Resource::isValid() const
{
	return type_ != Type::Undefined;
}


const QPixmap*
Resource::asPixmap() const
{
	return type_ == Type::Pixmap ? variant_.pixmap : nullptr;
}


Resource::Variant::Variant()
{}


Resource::Variant::Variant(const QPixmap* const pixmap) :
pixmap(pixmap)
{}
