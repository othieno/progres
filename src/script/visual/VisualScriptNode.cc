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
#include "VisualScriptNode.hh"
#include <QHash>
#include <QMimeDatabase>

using visualscript::VisualScriptNodeBase;


VisualScriptNodeBase::VisualScriptNodeBase(QQuickItem* const parent) :
QQuickItem(parent)
{}


const QString&
VisualScriptNodeBase::getSource() const
{
    return source_;
}


void
VisualScriptNodeBase::setSource(const QString& newSource)
{
    const auto trimmedSource = newSource.trimmed();
    if (source_ != trimmedSource) {
        source_ = trimmedSource;
        emit sourceChanged(source_);

        static const QMimeDatabase db;
        const QMimeType mimeType = db.mimeTypeForFile(source_);
        if (mimeType.isValid() && !mimeType.isDefault()) {
            const QStringList name = mimeType.name().split("/");
            const QString& category = name[0];
            const QString& type = name[1];

            if (sourceCategory_ != category) {
                sourceCategory_ = category;
                emit sourceCategoryChanged(sourceCategory_);
            }

            if (sourceType_ != type) {
                sourceType_ = type;
                emit sourceTypeChanged(sourceType_);
            }
        }
    }
}


const QString&
VisualScriptNodeBase::getSourceCategory() const {
    return sourceCategory_;
}


const QString&
VisualScriptNodeBase::getSourceType() const {
    return sourceType_;
}
