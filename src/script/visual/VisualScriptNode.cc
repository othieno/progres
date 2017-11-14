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
#include "VisualScriptNode.hh"
#include <QHash>
#include <QMimeDatabase>

using visualscript::VisualScriptNode;


VisualScriptNode::VisualScriptNode(QQuickItem* const parent) :
QQuickItem(parent),
type_(Type::Unspecified) {
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    QObject::connect(this, &VisualScriptNode::sourceChanged, this, &VisualScriptNode::loadSource);
}


VisualScriptNode::Type
VisualScriptNode::getType() const {
    return type_;
}


int
VisualScriptNode::getTypeAsInt() const {
    return static_cast<int>(type_);
}


const QString&
VisualScriptNode::getSource() const {
    return source_;
}


void
VisualScriptNode::setSource(const QString& source) {
    const auto trimmed = source.trimmed();
    if (source_ != trimmed) {
        source_ = trimmed;
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


void
VisualScriptNode::loadSource()
{
    const Type newNodeType = findNodeType(source_);
    if (newNodeType != type_) {
        type_ = newNodeType;
        emit typeChanged(static_cast<int>(type_));
    }
}


void
VisualScriptNode::registerType(const char* const uri)
{
    qmlRegisterType<VisualScriptNode>(uri, 1, 0, "VisualScriptNodeBase");
    qmlRegisterUncreatableMetaObject(
        nodetype::staticMetaObject, uri, 1, 0,
        "VisualScriptNodeType",
        "Access to the VisualScriptNodeType enum only"
    );
}


VisualScriptNode::Type
VisualScriptNode::findNodeType(const QString& filename)
{
    const QMimeDatabase db;
    const QHash<QString, Type> mapping = {
        {"image", Type::Image},
        {"audio", Type::Audio},
        {"video", Type::Video},
        {"text",  Type::SourceCode},
    };
    const QMimeType mime = db.mimeTypeForFile(filename);
    if (mime.isValid() && !mime.isDefault()) {
        const QString category = mime.name().split("/")[0];
        if (mapping.contains(category)) {
            return mapping[category];
        }
    }
    return Type::Unspecified;
}
