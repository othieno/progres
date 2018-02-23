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
#include "VisualScriptWire.hh"

using visualscript::Wire;


static constexpr std::size_t GEOMETRY_VERTEX_COUNT = 24;


Wire::Wire() :
Wire(nullptr, QPointF(0, 0), QPointF(0, 0))
{}


Wire::Wire(QQuickItem* const parent, const QPointF& start, const QPointF& end) :
QQuickItem(parent),
start_(start),
end_(end),
endpointChanged_(true),
geometry_(QSGGeometry::defaultAttributes_Point2D(), GEOMETRY_VERTEX_COUNT),
nodeDirtyState_(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial)
{
	geometry_.setDrawingMode(QSGGeometry::DrawLineStrip);
}


Wire::Wire(QQuickItem* const parent, const qreal startX, const qreal startY, const qreal endX, const qreal endY) :
Wire(parent, QPointF(startX, startY), QPointF(endX, endY))
{}


Wire::~Wire()
{}


qreal
Wire::getStartX() const
{
	return start_.x();
}


void
Wire::setStartX(const qreal startX)
{
	qreal& startX_ = start_.rx();
	if (startX_ != startX) {
		startX_ = startX;
		emit startXChanged(startX_);
		updateEndpoint();
	}
}


qreal
Wire::getStartY() const
{
	return start_.y();
}


void
Wire::setStartY(const qreal startY)
{
	qreal& startY_ = start_.ry();
	if (startY_ != startY) {
		startY_ = startY;
		emit startYChanged(startY_);
		updateEndpoint();
	}
}


qreal
Wire::getEndX() const
{
	return end_.x();
}


void
Wire::setEndX(const qreal endX)
{
	qreal& endX_ = start_.rx();
	if (endX_ != endX) {
		endX_ = endX;
		emit endXChanged(endX_);
		updateEndpoint();
	}
}


qreal
Wire::getEndY() const
{
	return end_.y();
}


void
Wire::setEndY(const qreal endY)
{
	qreal& endY_ = start_.ry();
	if (endY_ != endY) {
		endY_ = endY;
		emit endYChanged(endY_);
		updateEndpoint();
	}
}


const QColor&
Wire::getColor() const
{
	return material_.color();
}


void
Wire::setColor(const QColor& color)
{
	if (material_.color() != color) {
		material_.setColor(color);
		emit colorChanged(color);
		nodeDirtyState_.setFlag(QSGNode::DirtyMaterial);
		update();
	}
}


float
Wire::getThickness() const
{
	return geometry_.lineWidth();
}


void
Wire::setThickness(const float thickness)
{
	if (geometry_.lineWidth() != thickness) {
		geometry_.setLineWidth(thickness);
		emit thicknessChanged(thickness);
		nodeDirtyState_.setFlag(QSGNode::DirtyGeometry);
		update();
	}
}


QSGNode*
Wire::updatePaintNode(QSGNode* const oldNode, UpdatePaintNodeData* const)
{
	QSGGeometryNode* node = nullptr;
	if (oldNode == nullptr) {
		node = new QSGGeometryNode;
		node->setGeometry(&geometry_);
		node->setMaterial(&material_);
	} else {
		node = static_cast<QSGGeometryNode*>(oldNode);
	}
	if (endpointChanged_) {
		endpointChanged_ = false;
		updateBezierCurve();
		nodeDirtyState_.setFlag(QSGNode::DirtyGeometry);
	}
	node->markDirty(nodeDirtyState_);
	nodeDirtyState_ = 0;

	return node;
}


void
Wire::updateEndpoint()
{
	if (!endpointChanged_) {
		endpointChanged_ = true;
		update();
	}
}


void
Wire::updateBezierCurve()
{
	const QPointF& P0 = start_;
	const QPointF  Pn = end_;
	const QPointF  P1 = QPointF(P0.x() + 32, P0.y()) * 3; // x3 to factor the bezier function below.
	const QPointF& P2 = QPointF(Pn.x() - 32, Pn.y()) * 3;

	constexpr qreal N = 1.0 / qreal(GEOMETRY_VERTEX_COUNT - 1);
	QSGGeometry::Point2D* const vertices = geometry_.vertexDataAsPoint2D();
	for (std::size_t i = 0; i < GEOMETRY_VERTEX_COUNT; ++i) {
		const qreal x = i * N;
		const qreal o = 1.0 - x;
		const QPointF P =
			(P0 * o * o * o) +
			(P1 * o * o * x) +
			(P2 * o * x * x) +
			(Pn * x * x * x);

		vertices[i].set(P.x(), P.y());
	}
}
