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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "VisualScriptNodeBase.hh"

using visualscript::VisualScriptNodeBase;


VisualScriptNodeBase::VisualScriptNodeBase(QQuickItem* const parent) :
QQuickItem(parent),
type_(Type::Unspecified) {
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    QObject::connect(this, &VisualScriptNodeBase::sourceChanged, this, &VisualScriptNodeBase::loadSource);
}


VisualScriptNodeBase::Type
VisualScriptNodeBase::getType() const {
    return type_;
}


int
VisualScriptNodeBase::getTypeAsInt() const {
    return static_cast<int>(type_);
}


const QString&
VisualScriptNodeBase::getSource() const {
    return source_;
}


void
VisualScriptNodeBase::setSource(const QString& source) {
    const auto trimmed = source.trimmed();
    if (source_ != trimmed) {
        source_ = trimmed;
        emit sourceChanged(source_);
    }
}


const QString&
VisualScriptNodeBase::getName() const {
    return name_;
}


void
VisualScriptNodeBase::setName(const QString& name) {
    if (name_ != name) {
        name_ = name;
        emit nameChanged(name_);
    }
}


void
VisualScriptNodeBase::mousePressEvent(QMouseEvent* const event) {
    if (event->button() == Qt::LeftButton) {
        oldPosition_ = event->pos();
    }
}


void
VisualScriptNodeBase::mouseMoveEvent(QMouseEvent* const event) {
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


void
VisualScriptNodeBase::loadSource() {
}


void
VisualScriptNodeBase::registerType(const char* const uri)
{
    qmlRegisterType<VisualScriptNodeBase>(uri, 1, 0, "VisualScriptNodeBase");
    qmlRegisterUncreatableMetaObject(
        nodetype::staticMetaObject, uri, 1, 0,
        "VisualScriptNodeType",
        "Access to the VisualScriptNodeType enum only"
    );
}
