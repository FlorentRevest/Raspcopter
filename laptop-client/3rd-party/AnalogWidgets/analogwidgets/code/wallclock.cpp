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

#include <QtGui>
#include <cmath>
#include "wallclock.h"
#define PI 3.141592653589793238512808959406186204433

WallClock::WallClock(QWidget *parent)
    : WidgetWithBackground(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); 
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    
    


    setDigitOffset(75);
    setDateOffset(0);
    setTimeOffset(0); // -12
    setDayOffset(0); // 9

    setDigitColor(QColor(0,0,0));
    setDateColor(QColor(0,0,0));
    setTimeColor(QColor(0,0,192));
    setDayColor(QColor(0,96,0));

    m_digitFont.setPointSize(23);
    m_dateFont.setPointSize(21);
    m_timeFont.setPointSize(30);
    m_dayFont.setPointSize(16);

    // QWidget
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(tr("Analog Clock"));
    resize(220, 220);
    
    m_dateTime = QDateTime::currentDateTime(); 
    setShowCurrentDateTime(true); 
    
}

void WallClock::initCoordinateSystem(QPainter & painter)
{
    int side = qMin(width(), height());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 240.0, side / 240.0);
}

void WallClock::paintBackground(QPainter & painter)
{

    initCoordinateSystem(painter);
    // Malowanie obwiedni tarczy.
    //QColor ramka(17,50,214);// ³adny niebieski
    QColor ramka(215,0,0); // g³êboki czerwony
    // Gradient  zewnêtrznego okrêgu
    QRadialGradient back1(QPointF(0,0),135, QPointF(-27.5,110.0));
    back1.setColorAt(0.0,QColor(255,255,255));
    back1.setColorAt(1.0,ramka);
    // Gradient wewnêtrznego okrêgu
    QRadialGradient back2(QPoint(0,0),170, QPointF(57.5,100));
    back2.setColorAt(0.0,ramka);
    back2.setColorAt(1.0,QColor(255,255,255));

    QRadialGradient shield(QPointF(0,0),122,QPointF(-12.0,-15.0));
    shield.setColorAt(0.0,Qt::white);
    shield.setColorAt(0.5,QColor(240,240,240));
    shield.setColorAt(1.0,QColor(215,215,215));

    QPen Pen(Qt::black);
    Pen.setWidth(2);
    painter.setPen(Pen);

    // Koperta zegark
    painter.setBrush(QBrush(back1));
    painter.drawEllipse(-116,-116,232,232);
    painter.setBrush(QBrush(back2));

    painter.setPen(Qt::NoPen);
    painter.drawEllipse(-109,-109,218,218);

    painter.setPen(Pen);
    painter.setBrush(QBrush(shield));
    painter.drawEllipse(-102,-102,204,204);


    painter.setBrush(Qt::black);
    // rysowanie kó³ek godzin i samych godzin
    for (int i = 0; i < 12; ++i) {
        painter.drawEllipse(94, -2, 4, 4);
        painter.rotate(30.0);
    }


    // rysowanie kresek  minut
    painter.setPen(Qt::black);
    Pen.setWidth(2);
    painter.setPen(Pen);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(94, 0, 97, 0);
        painter.rotate(6.0);
    }

    QSize Size;
    QString Str;
    // Rysowanie cyfr na tarczy
    if (digitOffset()!=0.0)
    {
      painter.setFont(digitFont());
      painter.setPen(digitColor());
      for ( int z = 1; z <= 12; ++z) {
        QString hour = QString("%1").arg(z);
        Size = painter.fontMetrics().size(Qt::TextSingleLine, hour);
        painter.save();
        painter.translate(digitOffset() * cos(PI*z/6.0-PI/2.0),digitOffset() * sin(PI*z/6.0-PI/2.0));
        painter.setPen(digitColor());
        painter.drawText( QPointF ( Size.width()/ -2.0, Size.height() / 4.0), hour);
        painter.restore();
      }
    }

}// paintBackground


void WallClock::paintEvent(QPaintEvent *)
{
    static const int hourHand[8] = { -2, 18, 2, 18, 2, -60, -2, -60 };
    static const int minuteHand[8] = { -2, 28, 2, 28, 2, -80, -2, -80 };
    static const int secondHand[12] = {-1, 0, -1, -90, 1,-90, 1, 0, 4, 35, -4, 35};

    // odmalowywuje t³o
    drawBackground();
      // inicjalizacja paintera

    QPainter painter(this);
    initCoordinateSystem(painter);

    // Wyliczanie czasu i daty
    QTime time = m_dateTime.time(); 
    QDate date = m_dateTime.date(); 
    QString Str;
    QSize Size;

    if (timeOffset()!=0.0)
    {
      // Rysowanie tekstów - godziny
      painter.setFont(timeFont());
      painter.setPen(timeColor());
      Str = time.toString("hh:mm");
      Size = painter.fontMetrics().size(Qt::TextSingleLine, Str );
      painter.drawText( QPointF (Size.width() / -2.0, Size.height()+ timeOffset()) ,Str);
    }

    if (dateOffset()!=0.0)
    {
      // Rysowanie daty
      painter.setFont(dateFont());
      painter.setPen(dateColor());
      Str = date.toString("dd.MM.yyyy");
      Size = painter.fontMetrics().size(Qt::TextSingleLine, Str);
      painter.drawText( QPointF(Size.width() / -2.0,static_cast<int>(0 - dateOffset())), Str);
    }
    if (dayOffset()!=0.0)
    {
      // Dzieñ tygodnia
      painter.setFont(dayFont());
      painter.setPen(dayColor());
      Str =  date.toString("dddd");
      Size = painter.fontMetrics().size(Qt::TextSingleLine, Str);
      painter.drawText( QPointF (Size.width() / -2.0,static_cast<int>( 0 - dayOffset())) , Str);
    }

    // rysowanie wskazówki godzin
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(QPolygon(4, hourHand));
    painter.restore();

    // rysowanie minutnika
    painter.setBrush(Qt::black);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(QPolygon(4, minuteHand));
    painter.restore();

    // Malowanie wskazówki sekundnika
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.save();
    painter.rotate(6.0 * ( time.second())); //  + time.msec() / 1000.0) );
    painter.drawConvexPolygon(QPolygon(6, secondHand));
    painter.restore();
    // Kó³ko sekundnika
    painter.drawEllipse(-5,-5,10,10);
}// paintEvent 


void   WallClock::setTime ( const QTime & t)
{
  m_dateTime.setTime(t);
  setShowCurrentDateTime(false); 
  //update(); 
}


void   WallClock::setDate ( const QDate &d )
{
  m_dateTime.setDate(d);
  setShowCurrentDateTime(false); 
}


void   WallClock::setDateTime( const QDateTime &dt)
{
  m_dateTime = dt; 
  setShowCurrentDateTime(false);
}

void   WallClock::setShowCurrentDateTime(bool showCurrentDateTime)
{
  m_showCurrentDateTime = showCurrentDateTime; 
  if (m_showCurrentDateTime) 
    m_timer->start(); 
  else 
    m_timer->stop(); 
  update(); 
}

void WallClock::updateTime()
{
  m_dateTime = QDateTime::currentDateTime(); 
  if (isVisible())
    update();
}
