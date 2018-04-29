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
#include "ApplicationSettings.hh"

using progres::system::ApplicationSettings;


ApplicationSettings::ApplicationSettings() :
QSettings(QStringLiteral(APPLICATION_ORGANIZATION_NAME), QStringLiteral(APPLICATION_NAME))
{}


QVariant
ApplicationSettings::value(const Key key, const QVariant& defaultValue) const
{
	return QSettings::value(ApplicationSettings::getKeyName(key), defaultValue);
}


void
ApplicationSettings::setValue(const Key key, const QVariant& value)
{
	if (ApplicationSettings::value(key) != value) {
		QSettings::setValue(ApplicationSettings::getKeyName(key), value);
		emit valueChanged();
	}
}


QString
ApplicationSettings::getKeyName(const Key key, const bool withCategory)
{
	QString name;
	switch (key) {
		case Key::EnableOnboarding:
			name = "enableOnboarding";
			break;
		default:
			qFatal("[ApplicationSettings::getKeyName] Undefined key name!");
	}
	if (withCategory) {
		const Category category = getKeyCategory(key);
		if (category != Category::None) {
			name.prepend('/');
			name.prepend(ApplicationSettings::getCategoryName(category));
		}
	}
	return name;
}


ApplicationSettings::Category
ApplicationSettings::getKeyCategory(const Key key)
{
	switch (key) {
		case Key::EnableOnboarding:
			return Category::GrowthAndCommunications;
		default:
			return Category::None;
	}
}


QString
ApplicationSettings::getCategoryName(const Category category)
{
	switch (category) {
		case Category::GrowthAndCommunications:
			return QString("GrowthAndCommunications");
		case Category::Style:
			return QString("Style");
		case Category::None:
			return QString();
		default:
			qFatal("[ApplicationSettings::getCategoryName] Undefined category name!");
	}
}


bool
ApplicationSettings::isOnboardingEnabled() const
{
	return value(Key::EnableOnboarding, true).toBool();
}


void
ApplicationSettings::enableOnboarding(const bool enable)
{
	if (isOnboardingEnabled() != enable) {
		setValue(Key::EnableOnboarding, enable);
		emit onboardingToggled(enable);
	}
}
