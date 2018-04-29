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
#include "ResourceManager.hh"
#include "Application.hh"
#include "Resource.hh"
#include <QCryptographicHash>
#include <QUrl>
#include <QMimeDatabase>
#include <QFileInfo>

#define hash(s) QCryptographicHash::hash((s), QCryptographicHash::Md4).toHex()

using progres::system::ResourceManager;
using progres::system::Resource;


ResourceManager::ResourceManager(const Application& application) :
application_(application)
{}


QByteArray
ResourceManager::add(const QUrl& url)
{
	if (url.isLocalFile()) {
		const QFileInfo fileinfo(url.path());
		const QString& filename = fileinfo.canonicalFilePath();
		const QByteArray identifier = hash(filename.toUtf8());
		if (resources_.contains(identifier) && resources_[identifier] != nullptr) {
			return identifier;
		}
		if (fileinfo.isFile() && fileinfo.isReadable() && fileinfo.size() > 0) {
			Resource* const resource = createResourceFromLocalFile(filename);
			if (resource != nullptr) {
				resources_.insert(identifier, resource);
				emit resourceAdded(identifier);
				return identifier;
			}
		}
	} else {
		// TODO
	}
	return QByteArray();
}


void
ResourceManager::remove(const QByteArray& identifier)
{
	// TODO Free heap memory.
	if (resources_.contains(identifier)) {
		resources_.remove(identifier);
		emit resourceRemoved(identifier);
	}
}


const Resource*
ResourceManager::getResource(const QByteArray& identifier) const
{
	if (resources_.contains(identifier)) {
		return resources_[identifier];
	}
	return nullptr;
}


Resource*
ResourceManager::createResourceFromLocalFile(const QString& filename)
{
	const QMimeDatabase db;
	const QMimeType mimeType = db.mimeTypeForFile(filename);
	if (mimeType.isValid() && !mimeType.isDefault()) {
		const QString category = mimeType.name().split("/")[0];
		if (category == QStringLiteral("image")) {
			return new Resource(new QPixmap(filename));
		}
	}
	return nullptr;
}


Resource*
ResourceManager::createResourceFromRemoteFile(const QUrl&)
{
	// Download file to cache, then upload it to memory.
	return nullptr;
}
