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

    #include "bitmapbutton.h"
    #include "bitmapbutton_plugin.h" 
    #include "defines.h" 
    /*------------------------------------------------------------------------------------------------
     *			     			WALLCLCOCK    
     *------------------------------------------------------------------------------------------------*/

    BitmapButtonPlugin::BitmapButtonPlugin(QObject *parent)
        : QObject(parent)
    {
        initialized = false;
    }

    void BitmapButtonPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
    {
        if (initialized)
            return;

        initialized = true;
    }

    bool BitmapButtonPlugin::isInitialized() const
    {
        return initialized;
    }

    QWidget *BitmapButtonPlugin::createWidget(QWidget *parent)
    {
        return new BitmapButton(parent);
    }

    QString BitmapButtonPlugin::name() const
    {
        return QLatin1String("BitmapButton");
    }

    QString BitmapButtonPlugin::group() const
    {
        return QLatin1String("Analog Widgets");
    }

    QIcon BitmapButtonPlugin::icon() const
    {
        return QIcon();
    }

    QString BitmapButtonPlugin::toolTip() const
    {
        return QString();
    }

    QString BitmapButtonPlugin::whatsThis() const
    {
        return QString();
    }

    bool BitmapButtonPlugin::isContainer() const
    {
        return true;
    }

    QString BitmapButtonPlugin::domXml() const
    {
        return QLatin1String("<widget class=\"BitmapButton\" name=\"wallclock\">\n"
                             " <property name=\"geometry\">\n"
                             "  <rect>\n"
                             "   <x>0</x>\n"
                             "   <y>0</y>\n"
                             "   <width>64</width>\n"
                             "   <height>64</height>\n"
                             "  </rect>\n"
                             " </property>\n"
                             " <property name=\"toolTip\" >\n"
                             "  <string></string>\n"
                             " </property>\n"
                             " <property name=\"whatsThis\" >\n"
                             "  <string>"
                             "</string>\n"
                             " </property>\n"
                             "</widget>\n");
    }

    QString BitmapButtonPlugin::includeFile() const
    {
        return QLatin1String("analogwidgets/bitmapbutton.h");
    }

    QString BitmapButtonPlugin::codeTemplate() const
    {
        return QString();
    }

#ifdef SINGLEPLUGINS
    Q_EXPORT_PLUGIN(BitmapButtonPlugin)
#endif // SINGLEPLUGINS  
