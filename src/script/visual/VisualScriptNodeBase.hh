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
#ifndef VISUALSCRIPT_NODE_BASE_HH
#define VISUALSCRIPT_NODE_BASE_HH

#include <QQuickItem>


namespace visualscript {
/**
 * An enumeration of the available node types.
 */
namespace nodetype {
    Q_NAMESPACE
    enum class VisualScriptNodeType {
        Unspecified,
        Image,
        Audio,
        Video,
        SourceCode,
    };
    Q_ENUMS(VisualScriptNodeType)
}
/**
 *
 */
class VisualScriptNodeBase : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(int type READ getTypeAsInt NOTIFY typeChanged FINAL)
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
    using Type = nodetype::VisualScriptNodeType;

    explicit VisualScriptNodeBase(QQuickItem* const parent = nullptr);

    Type getType() const;
    int getTypeAsInt() const;
    const QString& getSource() const;
    void setSource(const QString& source);
    const QString& getName() const;
    void setName(const QString& name);
signals:
    void typeChanged(const int newType);
    void sourceChanged(const QString& newSource);
    void nameChanged(const QString& newName);
protected:
    void mousePressEvent(QMouseEvent* const event) override;
    void mouseMoveEvent(QMouseEvent* const event) override;
private:
    void loadSource();

    QString source_;
    QString name_;
    QPointF oldPosition_;
    Type type_;
};
} // namespace visualscript

#endif // VISUALSCRIPT_NODE_BASE_HH
