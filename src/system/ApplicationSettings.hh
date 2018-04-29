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
#ifndef PROGRES_SYSTEM_APPLICATIONSETTINGS_HH
#define PROGRES_SYSTEM_APPLICATIONSETTINGS_HH

#include <QSettings>


namespace progres {
namespace system {
/**
 *
 *
 */
class ApplicationSettings : public QSettings
{
	Q_OBJECT
	Q_PROPERTY(QString filename READ fileName CONSTANT)
	Q_PROPERTY(bool onboardingEnabled READ isOnboardingEnabled WRITE enableOnboarding NOTIFY onboardingToggled)
	friend class Application;
public:
	ApplicationSettings(const ApplicationSettings&) = delete;
	ApplicationSettings(ApplicationSettings&&) = delete;
	ApplicationSettings& operator=(const ApplicationSettings&) = delete;
	ApplicationSettings& operator=(ApplicationSettings&&) = delete;

	bool isOnboardingEnabled() const;
	void enableOnboarding(const bool enable);
private:
	/**
	 * An enumeration of available configuration keys.
	 */
	enum Key {
		EnableOnboarding,
	};
	/**
	 * An enumeration of available configuration categories.
	 */
	enum Category {
		GrowthAndCommunications,
		Style,
		None
	};
	/**
	 * \fn ApplicationSettings::ApplicationSettings()
	 * \brief Instantiates an ApplicationSettings object.
	 */
	ApplicationSettings();
	/**
	 * \fn QVariant ApplicationSettings::value(const Key key, const QVariant& defaultValue = QVariant())
	 * \brief Returns the value stored for the specified key.
	 * If no value is found, a default value will be returned.
	 */
	QVariant value(const Key key, const QVariant& defaultValue = QVariant()) const;
	/**
	 * \fn void ApplicationSettings::setValue(const Key key, const QVariant& value)
	 * \brief Stores the specified key's value.
	 * Returns true if the new value is different from the old and therefore changed, false otherwise.
	 */
	void setValue(const Key key, const QVariant& value);
	/**
	 * \fn QString ApplicationSettings::getKeyName(const Key key, const bool withCategory)
	 * \brief Returns the specified key's human-readable name.
	 */
	static QString getKeyName(const Key key, const bool withCategory = true);
	/**
	 * \fn Category ApplicationSettings::getKeyCategory(const Key key)
	 * \brief Returns the specified key's category.
	 */
	static Category getKeyCategory(const Key key);
	/**
	 * \fn QString ApplicationSettings::getCategoryName(const Category category)
	 * \brief Returns the specified category's human-readable name.
	 */
	static QString getCategoryName(const Category category);
signals:
	/**
	 * \fn void ApplicationSettings::valueChanged(const Key key)
	 * \brief A signal that is emitted when a value changes.
	 */
	void valueChanged();
	/**
	 * \fn void ApplicationSettings::onboardingToggled(const bool onboardingEnabled)
	 * \brief A signal that is emitted when onboarding is toggled.
	 */
	void onboardingToggled(const bool onboardingEnabled);
};
} // namespace system
} // namespace progres

#endif // PROGRES_SYSTEM_APPLICATIONSETTINGS_HH
