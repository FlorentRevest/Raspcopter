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

    #include "led.h" 
    #include "led_plugin.h"     
    #include "defines.h"  
    /*------------------------------------------------------------------------------------------------
     *			     			LED
     *------------------------------------------------------------------------------------------------*/
    
    
    LedPlugin::LedPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void LedPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool LedPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget *LedPlugin::createWidget(QWidget *parent)
    {
        return new Led(parent);
    }

    QString LedPlugin::name() const
    {
        return QLatin1String("Led");
    }

    QString LedPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon LedPlugin::icon() const
    {
        return QIcon();
    }

    QString LedPlugin::toolTip() const
    {
        return QString();
    }

    QString LedPlugin::whatsThis() const
    {
        return QString();
    }

    bool LedPlugin::isContainer() const
    {
        return false;
    }

    QString LedPlugin::domXml() const
    {
        return QLatin1String("<widget class=\"Led\" name=\"led\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>16</width>\n"
                             "   <height>16</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string>Color Led component</string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>Led indicator</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString LedPlugin::includeFile() const
    {
        return QLatin1String("analogwidgets/led.h");
    }

    QString LedPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS     
    Q_EXPORT_PLUGIN(LedPlugin)
#endif 
