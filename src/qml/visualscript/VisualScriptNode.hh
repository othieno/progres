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
#ifndef VISUALSCRIPT_NODE_HH
#define VISUALSCRIPT_NODE_HH

#include <QQuickItem>


namespace visualscript {
/**
 *
 */
class VisualScriptNode : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
    explicit VisualScriptNode(QQuickItem* const parent = nullptr);

    const QString& getName() const;
    void setName(const QString& name);
signals:
    void nameChanged(const QString& newName);
private:
    QString name_;
};
} // namespace visualscript

#endif // VISUALSCRIPT_NODE_HH
