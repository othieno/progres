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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef VISUALSCRIPT_ITEM_HH
#define VISUALSCRIPT_ITEM_HH

#include <QQuickItem>


namespace visualscript {
/**
 *
 */
class Item : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(qreal globalX READ getGlobalX NOTIFY globalXChanged)
	Q_PROPERTY(qreal globalY READ getGlobalY NOTIFY globalYChanged)
public:
	explicit Item(Item* parent = nullptr);
	/**
	 * Returns the item's X position relative to the root node.
	 */
	virtual qreal getGlobalX() const;
	/**
	 * Returns the item's Y position relative to the root node.
	 */
	virtual qreal getGlobalY() const;
signals:
	/**
	 * A signal that is emitted when the item's global X position is changed.
	 */
	void globalXChanged(const qreal x);
	/**
	 * A signal that is emitted when the item's global Y position is changed.
	 */
	void globalYChanged(const qreal y);
};
} // namespace visualscript

#endif // VISUALSCRIPT_ITEM_HH
