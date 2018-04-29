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
#include "ResourceImageProvider.hh"
#include "Resource.hh"

using progres::ui::ResourceImageProvider;
using progres::system::ResourceManager;
using progres::system::Resource;


ResourceImageProvider::ResourceImageProvider(const ResourceManager& resourceManager) :
QQuickImageProvider(QQmlImageProviderBase::Pixmap, QQmlImageProviderBase::ForceAsynchronousImageLoading),
resourceManager_(resourceManager)
{}


QPixmap
ResourceImageProvider::requestPixmap(const QString& id, QSize* const size, const QSize& requestedSize)
{
	const auto* resource = resourceManager_.getResource(id.toUtf8());
	if (resource != nullptr && resource->getType() == Resource::Type::Pixmap) {
		const QPixmap* pixmap = resource->asPixmap();
		if (pixmap != nullptr) {
			if (size != nullptr) {
				*size = pixmap->size();
			}
			return requestedSize.isEmpty() ? *pixmap : pixmap->scaled(requestedSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
		}
	}
	return QPixmap();
}
