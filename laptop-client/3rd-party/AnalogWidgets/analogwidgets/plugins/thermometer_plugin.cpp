/***************************************************************************
 *   Copyright (C) 2006-2008 by Tomasz Ziobrowski                          *
 *   http://www.3electrons.com                                             *
 *   e-mail: t.ziobrowski@3electrons.com                                   *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

    #include "thermometer.h"
    #include "thermometer_plugin.h"
    #include "defines.h"
    /*------------------------------------------------------------------------------------------------
     *			     			MANOMETER
     *------------------------------------------------------------------------------------------------*/


    ThermoMeterPlugin::ThermoMeterPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void ThermoMeterPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool ThermoMeterPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget *ThermoMeterPlugin::createWidget(QWidget *parent)
    {
        return new ThermoMeter(parent);
    }

    QString ThermoMeterPlugin::name() const
    {
        return QLatin1String("ThermoMeter");
    }

    QString ThermoMeterPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon ThermoMeterPlugin::icon() const
    {
        return QIcon();
    }

    QString ThermoMeterPlugin::toolTip() const
    {
        return QString();
    }

    QString ThermoMeterPlugin::whatsThis() const
    {
        return QString();
    }

    bool ThermoMeterPlugin::isContainer() const
    {
        return false;
    }

    QString ThermoMeterPlugin::domXml() const
    {
        return QLatin1String("<widget class=\"ThermoMeter\" name=\"thermometer\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>40</width>\n"
                             "   <height>160</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string>Shows the pressure</string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>The bar meter widget displays "
                             "the pressure attached to it</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString ThermoMeterPlugin::includeFile() const
    {
        return QLatin1String("analogwidgets/thermometer.h");
    }

    QString ThermoMeterPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS
    Q_EXPORT_PLUGIN(ThermoMeterPlugin)
#endif
