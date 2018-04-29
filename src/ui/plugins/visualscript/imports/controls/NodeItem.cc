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
#include "NodeItem.hh"

using visualscript::NodeItem;


NodeItem::NodeItem(QQuickItem* const parent) :
QQuickItem(parent),
node_(nullptr),
relativePositionChanged_(true),
relativeX_(0),
relativeY_(0)
{}


void
NodeItem::componentComplete()
{
	QQuickItem::componentComplete();

	connect(this, &QQuickItem::xChanged, this, &NodeItem::updateRelativePosition);
	connect(this, &QQuickItem::yChanged, this, &NodeItem::updateRelativePosition);

	// Find the Node while remembering the path to it. These intermediary parents
	// will be used to calculate the NodeItem's position relative to the Node.
	QList<const QQuickItem*> ancestry;
	for (QQuickItem* parent = parentItem(); parent != nullptr; parent = parent->parentItem()) {
		// The node has a special property which is used to locate it.
		// Please refer to Node.qml for more information.
		if (parent->property("__VISUALSCRIPT_NODE__").toBool()) {
			node_ = parent;
			connect(node_, &QQuickItem::xChanged, this, &NodeItem::absoluteXChanged);
			connect(node_, &QQuickItem::yChanged, this, &NodeItem::absoluteYChanged);
			break;
		} else {
			ancestry.append(parent);
		}
	}
	if (node_ != nullptr) {
		for (const auto* node : ancestry) {
			connect(node, &QQuickItem::xChanged, this, &QQuickItem::xChanged);
			connect(node, &QQuickItem::yChanged, this, &QQuickItem::yChanged);
		}
	}
}


QQuickItem*
NodeItem::getNode()
{
	return node_;
}


const QQuickItem*
NodeItem::getNode() const
{
	return node_;
}


qreal
NodeItem::getAbsoluteX() const
{
	return node_ == nullptr ? x() : node_->x() + getRelativeX();
}


qreal
NodeItem::getAbsoluteY() const
{
	return node_ == nullptr ? y() : node_->y() + getRelativeY();
}


qreal
NodeItem::getRelativeX() const
{
	calculateRelativePosition();
	return relativeX_;
}


qreal
NodeItem::getRelativeY() const
{
	calculateRelativePosition();
	return relativeY_;
}


void
NodeItem::updateRelativePosition()
{
	relativePositionChanged_ = true;
	emit absoluteXChanged();
	emit absoluteYChanged();
}


void
NodeItem::calculateRelativePosition() const
{
	if (relativePositionChanged_) {
		relativePositionChanged_ = false;
		relativeX_ = x();
		relativeY_ = y();
		if (node_ != nullptr) {
			for (const QQuickItem* parent = parentItem(); parent != node_; parent = parent->parentItem()) {
				relativeX_ += parent->x();
				relativeY_ += parent->y();
			}
		}
	}
}
