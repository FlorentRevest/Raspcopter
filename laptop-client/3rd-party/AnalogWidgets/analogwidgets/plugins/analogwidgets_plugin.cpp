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
#include <QtPlugin>
#include "analogwidgets_plugin.h"
#include "defines.h"

#include "wallclock_plugin.h"
#include "manometer_plugin.h"
#include "thermometer_plugin.h" 
#include "chart_plugin.h" 
#include "bitmapbutton_plugin.h" 
//#include "wheel/wheel_plugin.h"
//#include "mnemonicbox_plugin.h" 
#include "led_plugin.h"
#include "counter_plugin.h" 
#include "scriptwidget_plugin.h" 
#include "potentiometer_plugin.h" 

AnalogWidgetsPlugin::AnalogWidgetsPlugin()
{
  m_pluginList.push_back(new WallClockPlugin(NULL));
  m_pluginList.push_back(new ManoMeterPlugin(NULL));
  m_pluginList.push_back(new ThermoMeterPlugin(NULL));
  m_pluginList.push_back(new ChartPlugin(NULL)); 
  m_pluginList.push_back(new LedPlugin(NULL));
  m_pluginList.push_back(new PotentioMeterPlugin(NULL));   
  m_pluginList.push_back(new CounterPlugin(NULL));
  m_pluginList.push_back(new BitmapButtonPlugin(NULL)); 
  m_pluginList.push_back(new ScriptWidgetPlugin(NULL));
  
 // m_pluginList.push_back(new WheelPlugin(NULL)); 
 // m_pluginList.push_back(new MnemonicBoxPlugin(NULL)); 
}

AnalogWidgetsPlugin::~AnalogWidgetsPlugin()
{
  QList<QDesignerCustomWidgetInterface *>::Iterator i = m_pluginList.begin();
  while (i != m_pluginList.end())
  delete *i++;
  m_pluginList.clear();
}

QList<QDesignerCustomWidgetInterface *>
AnalogWidgetsPlugin:: customWidgets() const
{
  return m_pluginList;
}

#ifndef SINGLEPLUGINS
Q_EXPORT_PLUGIN(AnalogWidgetsPlugin)
#endif
