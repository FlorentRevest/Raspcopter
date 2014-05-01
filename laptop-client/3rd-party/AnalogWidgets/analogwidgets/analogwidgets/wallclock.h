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

#ifndef WALLCLOCK_H
#define WALLCLOCK_H
#include <QDateTime> 
#include <QTimer> 

#include "widgetwithbackground.h"
 
    class WallClock : public WidgetWithBackground 
    {
        Q_OBJECT
	Q_PROPERTY (QFont digitFont READ digitFont WRITE setDigitFont)
	Q_PROPERTY (QFont dateFont  READ dateFont  WRITE setDateFont)
	Q_PROPERTY (QFont timeFont  READ timeFont  WRITE setTimeFont)
	Q_PROPERTY (QFont dayFont   READ dayFont   WRITE setDayFont)

	Q_PROPERTY (int digitOffset READ digitOffset WRITE setDigitOffset) //RESET resetDigitOffset)
	Q_PROPERTY (int dateOffset  READ dateOffset  WRITE setDateOffset ) //RESET resetDateOffset )
	Q_PROPERTY (int timeOffset  READ timeOffset  WRITE setTimeOffset ) //RESET resetTimeOffset )
	Q_PROPERTY (int dayOffset   READ dayOffset   WRITE setDayOffset  ) //RESET resetDayOffset  )

	Q_PROPERTY (QColor digitColor READ digitColor WRITE setDigitColor)
	Q_PROPERTY (QColor dateColor  READ dateColor  WRITE setDateColor)
	Q_PROPERTY (QColor timeColor  READ timeColor  WRITE setTimeColor)
	Q_PROPERTY (QColor dayColor   READ dayColor   WRITE setDayColor)
        Q_PROPERTY (QDateTime  dateTime       READ dateTime       WRITE setDateTime)
        Q_PROPERTY (bool showCurrentDateTime READ showCurrentDateTime WRITE setShowCurrentDateTime) 
    public:
	WallClock(QWidget *parent = 0);

    	QFont digitFont() const    { return m_digitFont;}
  	QFont timeFont () const    { return m_timeFont; }
    	QFont dateFont () const    { return m_dateFont; }
    	QFont dayFont  () const    { return m_dayFont;  }

    	void setDigitFont(QFont f) {        m_digitFont = f; updateWithBackground();}
    	void setTimeFont (QFont f) {        m_timeFont  = f; updateWithBackground();}
    	void setDateFont (QFont f) {        m_dateFont  = f; updateWithBackground();}
	void setDayFont  (QFont f) {        m_dayFont   = f; updateWithBackground();}

	int     digitOffset () const { return m_digitOffset; }
	int      dateOffset () const { return m_dateOffset;  }
	int      timeOffset () const { return m_timeOffset;  }
	int      dayOffset  () const { return m_dayOffset;   }
	void  setDigitOffset(int i)  {        m_digitOffset = i; updateWithBackground();}
	void  setDateOffset (int i)  {        m_dateOffset  = i; updateWithBackground();}
	void  setTimeOffset (int i)  {        m_timeOffset  = i; updateWithBackground();}
	void  setDayOffset  (int i)  {        m_dayOffset   = i; updateWithBackground();}

	QColor    digitColor() const  { return m_digitColor;   }
	QColor    dateColor() const   { return m_dateColor;    }
	QColor    timeColor() const   { return m_timeColor;    }
	QColor    dayColor()  const   { return m_dayColor;     }
        QDateTime dateTime()  const   { return m_dateTime;     }
        QDate     date()      const   { return m_dateTime.date(); }
        QTime     time()      const   { return m_dateTime.time(); } 
        bool      showCurrentDateTime() const { return m_showCurrentDateTime; } 
        
	void   setDigitColor(QColor c){        m_digitColor = c; updateWithBackground();}
	void   setDateColor(QColor c) {        m_dateColor = c;  updateWithBackground();}
	void   setTimeColor(QColor c) {        m_timeColor = c;  updateWithBackground();}
	void   setDayColor (QColor c) {        m_dayColor  = c;  updateWithBackground();}
        
      public slots:
        
        void   setTime ( const QTime & ); 
        void   setDate ( const QDate & ); 
        void   setDateTime( const QDateTime &); 
        void   setShowCurrentDateTime(bool showCurrentDateTime); 
      protected slots: 
        void updateTime(); 
        
    protected:

	
        void paintEvent(QPaintEvent *event);
	void paintBackground(QPainter & painter);
	void initCoordinateSystem(QPainter & painter);
	 
	
	int resetDigitOffset() const { return 75; }
	int resetDateOffset()  const { return 0;  }
	int resetTimeOffset()  const { return -12;}
	int resetDayOffset()   const { return 29; }


        QFont m_digitFont;
        QFont m_dateFont;
        QFont m_timeFont;
        QFont m_dayFont;

        int   m_digitOffset;
        int   m_dateOffset;
        int   m_timeOffset;
        int   m_dayOffset;

        QColor m_digitColor;
        QColor m_dateColor;
        QColor m_timeColor;
        QColor m_dayColor;
        QDateTime m_dateTime; 
        bool m_showCurrentDateTime; 
        QTimer * m_timer; 
    };
#endif // WALLCLOCK_H
