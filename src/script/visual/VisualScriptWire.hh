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
#ifndef VISUALSCRIPT_WIRE_HH
#define VISUALSCRIPT_WIRE_HH

#include <QQuickItem>
#include <QSGNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>


namespace visualscript {
/**
 * A Wire is a visual representation of a link between two points.
 */
class Wire : public QQuickItem {
	Q_OBJECT
	Q_PROPERTY(qreal startX READ getStartX WRITE setStartX NOTIFY startXChanged)
	Q_PROPERTY(qreal startY READ getStartY WRITE setStartY NOTIFY startYChanged)
	Q_PROPERTY(qreal endX READ getEndX WRITE setEndX NOTIFY endXChanged)
	Q_PROPERTY(qreal endY READ getEndY WRITE setEndY NOTIFY endYChanged)
	Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(float thickness READ getThickness WRITE setThickness NOTIFY thicknessChanged)
public:
	Wire();
	Wire(QQuickItem* const parent, const QPointF& start, const QPointF& end);
	Wire(QQuickItem* const parent, const qreal startX, const qreal startY, const qreal endX, const qreal endY);
	~Wire();

	qreal getStartX() const;
	void setStartX(const qreal startX);

	qreal getStartY() const;
	void setStartY(const qreal startY);

	qreal getEndX() const;
	void setEndX(const qreal endX);

	qreal getEndY() const;
	void setEndY(const qreal endY);

	const QColor& getColor() const;
	void setColor(const QColor& color);

	float getThickness() const;
	void setThickness(const float thickness);
protected:
	QSGNode* updatePaintNode(QSGNode* const, UpdatePaintNodeData* const) Q_DECL_OVERRIDE;
private:
	void updateEndpoint();
	void updateBezierCurve();

	QPointF start_;
	QPointF end_;
	bool endpointChanged_;
	QSGGeometry geometry_;
	QSGFlatColorMaterial material_;
	QSGNode::DirtyState nodeDirtyState_;
signals:
	void startXChanged(const qreal startX);
	void startYChanged(const qreal startY);
	void endXChanged(const qreal endX);
	void endYChanged(const qreal endY);
	void colorChanged(const QColor& color);
	void thicknessChanged(const float thickness);
};
} // namespace visualscript

#endif // VISUALSCRIPT_WIRE_HH
