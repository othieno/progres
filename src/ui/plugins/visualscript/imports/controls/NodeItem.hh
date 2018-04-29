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
#ifndef VISUALSCRIPT_NODEITEM_HH
#define VISUALSCRIPT_NODEITEM_HH

#include <QQuickItem>


namespace visualscript {
/**
 * A NodeItem is an Item that is strictly a component of a Node.
 */
class NodeItem : public QQuickItem
{
	Q_OBJECT
	Q_PROPERTY(QQuickItem* node READ getNode CONSTANT FINAL)
	Q_PROPERTY(qreal absoluteX READ getAbsoluteX NOTIFY absoluteXChanged FINAL)
	Q_PROPERTY(qreal absoluteY READ getAbsoluteY NOTIFY absoluteYChanged FINAL)
public:
	explicit NodeItem(QQuickItem* const parent = nullptr);
	/**
	 * \see QQuickItem::componentComplete.
	 */
	void componentComplete() override;
	/**
	 * \fn QQuickItem* getNode()
	 * \brief Returns a pointer to the node that this NodeItem is a descendant of.
	 */
	QQuickItem* getNode();
	/**
	 * \fn QQuickItem* getNode()
	 * \brief Returns a const pointer to the node that this NodeItem is a descendant of.
	 */
	const QQuickItem* getNode() const;
	/**
	 * \fn qreal getAbsoluteX() const
	 * \brief Returns the item's absolute X position.
	 */
	qreal getAbsoluteX() const;
	/**
	 * \fn qreal getAbsoluteY() const
	 * \brief Returns the item's absolute Y position.
	 */
	qreal getAbsoluteY() const;
private:
	/**
	 * \fn qreal getRelativeX() const
	 * \brief Returns the item's relative X position.
	 */
	qreal getRelativeX() const;
	/**
	 * \fn qreal getRelativeY() const
	 * \brief Returns the item's relative Y position.
	 */
	qreal getRelativeY() const;
	/**
	 * \fn void updateRelativePosition()
	 * \brief Signals that the NodeItem's relative position needs to be updated.
	 */
	void updateRelativePosition();
	/**
	 * \fn void calculateRelativePosition()
	 * \brief Calculates the item's relative position.
	 */
	void calculateRelativePosition() const;

	QQuickItem* node_;
	mutable bool relativePositionChanged_;
	mutable qreal relativeX_;
	mutable qreal relativeY_;
signals:
	/**
	 * \brief A signal that is emitted when the item's absolute X position is changed.
	 */
	void absoluteXChanged();
	/**
	 * \brief A signal that is emitted when the item's absolute Y position is changed.
	 */
	void absoluteYChanged();
};
} // namespace visualscript

#endif // VISUALSCRIPT_NODEITEM_HH
