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
#ifndef PROGRES_UI_RESOURCEIMAGEPROVIDER_HH
#define PROGRES_UI_RESOURCEIMAGEPROVIDER_HH

#include <QQuickImageProvider>
#include "ResourceManager.hh"


namespace progres {
namespace ui {
/**
 *
 */
class ResourceImageProvider : public QQuickImageProvider
{
	friend class GraphicalUserInterface;
public:
	QPixmap requestPixmap(const QString& id, QSize* const size, const QSize& requestedSize) override;
private:
	explicit ResourceImageProvider(const system::ResourceManager& resourceManager);

	const system::ResourceManager& resourceManager_;
};
} // namespace ui
} // namespace progres

#endif // PROGRES_UI_RESOURCEIMAGEPROVIDER_HH
