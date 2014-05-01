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

    #include "chart.h"
    #include "chart_plugin.h"
    #include "defines.h"
 
    /*------------------------------------------------------------------------------------------------
     *			     			CHART
     *------------------------------------------------------------------------------------------------*/

    ChartPlugin::ChartPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void ChartPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool ChartPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget * ChartPlugin::createWidget(QWidget *parent)
    {
          return new Chart(parent);
    }

    QString ChartPlugin::name() const
    {
            return QLatin1String("Chart");
    }

    QString ChartPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon ChartPlugin::icon() const
    {
        return QIcon();
    }

    QString ChartPlugin::toolTip() const
    {
        return QString();
    }

    QString ChartPlugin::whatsThis() const
    {
        return QString();
    }

    bool ChartPlugin::isContainer() const
    {
         return false;
    }

    QString ChartPlugin::domXml() const
    {
     	 return QLatin1String("<widget class=\"Chart\" name=\"chart\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>300</width>\n"
                             "   <height>200</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string>Draws an charts</string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>The chart draws "
                             "time diagrams</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString ChartPlugin::includeFile() const
    {
       return QLatin1String("analogwidgets/chart.h");
    }

    QString ChartPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS
    Q_EXPORT_PLUGIN(ChartPlugin)
#endif
