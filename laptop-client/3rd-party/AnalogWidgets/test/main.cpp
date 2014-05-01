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

    #include <QApplication>
    #include <QObject>

    #include "test.h"


    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);
        TestWidget widget;


    //#ifdef Q_WS_S60
       // QFont f = window.font();
       // f.setPixelSize(12);
        //widget.setFont(f);
        widget.showFullScreen();
        //widget.showMaximized();
    //else 
    //    widget.resize(240,300);
    //    widget.show();
    //#endif

       // app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
        return app.exec();
    }
