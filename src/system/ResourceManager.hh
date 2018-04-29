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
#ifndef PROGRES_SYSTEM_RESOURCEMANAGER_HH
#define PROGRES_SYSTEM_RESOURCEMANAGER_HH

#include <QObject>
#include <QHash>


namespace progres {
namespace system {
/**
 *
 */
class Application;
/**
 *
 */
class Resource;
/**
 *
 */
class ResourceManager : public QObject
{
	Q_OBJECT
	friend class Application;
public:
	/**
	 *
	 */
	Q_INVOKABLE QByteArray add(const QUrl& url);
	/**
	 *
	 */
	Q_INVOKABLE void remove(const QByteArray& identifier);
	/**
	 * \brief Returns a pointer to the resource with the specified identifier.
	 */
	const Resource* getResource(const QByteArray& identifier) const;
private:
	explicit ResourceManager(const Application&);

	static Resource* createResourceFromLocalFile(const QString& filename);
	static Resource* createResourceFromRemoteFile(const QUrl& url);

	const Application& application_;
	QHash<QByteArray, Resource*> resources_;
signals:
	void resourceAdded(const QByteArray& identifier);
	void resourceRemoved(const QByteArray& identifier);
};
} // namespace system
} // namespace progres

#endif // PROGRES_SYSTEM_RESOURCEMANAGER_HH
