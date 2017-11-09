/*
 * This file is part of PROGRES (Procedural Graphics Editor Suite).
 * Copyright (C) 2017, Jeremy Othieno.
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "VisualScriptNode.hh"

using visualscript::VisualScriptNode;


VisualScriptNode::VisualScriptNode(QQuickItem* const parent) :
QQuickItem(parent),
type_(Type::Unspecified) {
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}


const QString&
VisualScriptNode::getSource() const {
    return source_;
}


void
VisualScriptNode::setSource(const QString& source) {
    if (source_ != source) {
        source_ = source;
        emit sourceChanged(source_);
    }
}


const QString&
VisualScriptNode::getName() const {
    return name_;
}


void
VisualScriptNode::setName(const QString& name) {
    if (name_ != name) {
        name_ = name;
        emit nameChanged(name_);
    }
}


void
VisualScriptNode::mousePressEvent(QMouseEvent* const event) {
    if (event->button() == Qt::LeftButton) {
        oldPosition_ = event->pos();
    }
}


void
VisualScriptNode::mouseMoveEvent(QMouseEvent* const event) {
    if (event->buttons() & Qt::LeftButton) {
        constexpr int DEADZONE = 3;
        auto newPosition = event->pos() - oldPosition_;
        if (newPosition.manhattanLength() >= DEADZONE) {
            static const auto clamp = [](qreal& value, const qreal max) {
                if (value < 0.0) {
                    value = 0.0;
                } else if (value > max) {
                    value = max;
                }
            };

            const auto* parent = parentItem();
            newPosition = mapToItem(parent, newPosition);

            clamp(newPosition.rx(), parent->width() - width());
            clamp(newPosition.ry(), parent->height() - height());

            setPosition(newPosition);
        }
    }
}
