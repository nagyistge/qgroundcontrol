/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "ValuesWidgetController.h"

#include <QSettings>

const char* ValuesWidgetController::_groupKey =         "ValuesWidget";
const char* ValuesWidgetController::_largeValuesKey =   "large";
const char* ValuesWidgetController::_smallValuesKey =   "small";

ValuesWidgetController::ValuesWidgetController(void)
{
    QSettings settings;
    QStringList largeDefaults;

    settings.beginGroup(_groupKey);

    largeDefaults << "Vehicle.altitudeRelative" << "Vehicle.groundSpeed";
    _largeValues = settings.value(_largeValuesKey, largeDefaults).toStringList();
    _smallValues = settings.value(_smallValuesKey, QStringList()).toStringList();

    _altitudeProperties << "altitudeRelative" << "altitudeAMSL";

    // Keep back compat for removed WGS84 value
    if (_largeValues.contains ("Vehicle.altitudeWGS84")) {
        setLargeValues(_largeValues.replaceInStrings("Vehicle.altitudeWGS84", "Vehicle.altitudeRelative"));
    }
    if (_smallValues.contains ("Vehicle.altitudeWGS84")) {
        setSmallValues(_largeValues.replaceInStrings("Vehicle.altitudeWGS84", "Vehicle.altitudeRelative"));
    }
}

void ValuesWidgetController::setLargeValues(const QStringList& values)
{
    QSettings settings;

    settings.beginGroup(_groupKey);
    settings.setValue(_largeValuesKey, values);

    _largeValues = values;
    emit largeValuesChanged(values);
}

void ValuesWidgetController::setSmallValues(const QStringList& values)
{
    QSettings settings;

    settings.beginGroup(_groupKey);
    settings.setValue(_smallValuesKey, values);

    _smallValues = values;
    emit smallValuesChanged(values);
}
