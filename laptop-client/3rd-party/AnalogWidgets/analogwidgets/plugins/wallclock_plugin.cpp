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

    #include "wallclock.h"
    #include "wallclock_plugin.h" 
    #include "defines.h" 
    /*------------------------------------------------------------------------------------------------
     *			     			WALLCLCOCK    
     *------------------------------------------------------------------------------------------------*/

    WallClockPlugin::WallClockPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void WallClockPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool WallClockPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget *WallClockPlugin::createWidget(QWidget *parent)
    {
        return new WallClock(parent);
    }

    QString WallClockPlugin::name() const
    {
        return QLatin1String("WallClock");
    }

    QString WallClockPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon WallClockPlugin::icon() const
    {
        return QIcon();
    }

    QString WallClockPlugin::toolTip() const
    {
        return QString();
    }

    QString WallClockPlugin::whatsThis() const
    {
        return QString();
    }

    bool WallClockPlugin::isContainer() const
    {
        return false;
    }

    QString WallClockPlugin::domXml() const
    {
        return QLatin1String("<widget class=\"WallClock\" name=\"wallclock\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>100</width>\n"
                             "   <height>100</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string>The current time and date</string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>The analog clock widget displays "
                             "the current time and date.</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString WallClockPlugin::includeFile() const
    {
        return QLatin1String("analogwidgets/wallclock.h");
    }

    QString WallClockPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS
    Q_EXPORT_PLUGIN(WallClockPlugin)
#endif // SINGLEPLUGINS  
