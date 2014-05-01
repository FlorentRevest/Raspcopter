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

#include "widgettester.h"
#include "abstractmeter.h"


	WidgetTester::WidgetTester(QObject * parent,AbstractMeter * meter):QObject(parent)
	{

	  m_meter = meter;

          int range = static_cast<int>(m_meter ->maximum() - m_meter->minimum());
	  int inc_delay = 250;
          int dec_delay = 1000;
	  int stop_delay = 100;


          inc = range / (inc_delay / 5 );
	  dec = range / (dec_delay / 5 );

	  if (!inc) inc = 1;
          if (!dec) dec = 1;
          incTimer = new QTimer(parent);
	  decTimer = new QTimer(parent);
	  stopTimer = new QTimer(parent);
	  stopTimer->setInterval(stop_delay);
	  stopTimer->setSingleShot(true);

	 decTimer->setInterval(5);
	 connect(incTimer, SIGNAL(timeout()),this,SLOT(Increment()));
	 connect(stopTimer,SIGNAL(timeout()),decTimer,SLOT(start()));
	 connect(decTimer, SIGNAL(timeout()),this,SLOT(Decrement()));
        }

        void WidgetTester::start()
        {
	 m_meter->setValue(m_meter->minimum());
         incTimer->start(5);

        }

	void WidgetTester::Increment()
        {
	 m_meter->setValue(m_meter->value()+inc); // meter->value()+inc);
	 if (m_meter->value() > m_meter->maximum() )
         {
           incTimer->stop();
	   stopTimer->start();
         }

	}

	void WidgetTester::Decrement()
	{
	  m_meter->setValue(m_meter->value()-dec);
	 if (m_meter->value() < m_meter->minimum() )
	 {
           decTimer->stop();
	   m_meter->setValue(m_meter->minimum());
         }
	}
