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
#include <QPainter> 
#include <QMouseEvent> 
#include <QLineF> 
#include <QPointF> 


#include "potentiometer.h" 

PotentioMeter::PotentioMeter(QWidget * parent):QAbstractSlider(parent)
{
 init();
}

int PotentioMeter::rotationRange() const
{
  return m_rotationRange; 
}

QString PotentioMeter::svgResourceFile() const
{
  return m_filePath; 
}
/*---------------------------------------------------------------------------
				PUBLIC SLOTS 
---------------------------------------------------------------------------*/
void PotentioMeter::setRotationRange(int rotationRange)
{
   m_rotationRange = rotationRange; 
}

void PotentioMeter::setSvgResourceFile( const QString & filePath )
{
   m_filePath = filePath; 
   if (m_renderer) 
       delete m_renderer; 
   m_renderer = new QSvgRenderer(this);


   if (!m_renderer->load(filePath)) 
   { 
     qDebug("PotentioMeter::setSvgResourceFile can't load file %s",qPrintable(m_filePath));    
     m_filePath = ":/default/resources/dial1.svg"; 
     m_renderer->load(m_filePath);
   }
   else 
      qDebug("PotentioMeter::setSvgResourceFile %s loaded",qPrintable(m_filePath));    
  
   update(); 
}
/*---------------------------------------------------------------------------
				PROTECTED
---------------------------------------------------------------------------*/
void PotentioMeter::paintEvent(QPaintEvent *)
{ 
   
    //qDebug("PotentioMeter::paintEvent() value %d",value());
    QPainter painter(this);
    int side = qMin(width(), height());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 240.0, side / 240.0);

    // Rysowanie Kropki 
    int rRange = rotationRange(); 
    m_value = value() - minimum(); 
    int paintValue = m_value % rRange; 
    double step_angle = 360.0/rRange; 

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    QRectF frame(QPointF(-115,-115),QPointF(115,115));

    m_renderer->render(&painter,QString("background"),frame); 
    painter.save();

    
    painter.rotate(paintValue * step_angle ) ; 
    
    m_renderer->render(&painter,QString("foreground"), frame); //,QString("background"),frame); 
    //m_renderer->render(&painter,QString("foreground"),frame); 
    //painter.drawRect(-5,-100,10,30); 
    painter.restore();

}// paintEvent 

void PotentioMeter::mouseMoveEvent(QMouseEvent * event)
{
  if (event->buttons() & Qt::LeftButton) 
  {
     int x = event->x();
     int y = event->y();
      QLineF line(width()/2,height()/2,width()/2,0);
      QLineF line2(width()/2,height()/2,width(),height());
      QLineF prev(width()/2,height()/2,x,y);
      qreal angle = prev.angleTo(line);
      qreal angle2 = prev.angleTo(line2); 
      int rRange = rotationRange()+1;
      
       int  m_inc = (angle*rRange) / 360.0;
        int v=0; 
       if (value()%rRange - m_inc != 0 && m_inc != 0) 
       { 
		if (angle > 90.0 && angle < 270.0)
		{	
		 if (m_prevAngle < angle )
                   v = 1; 

		 if (m_prevAngle > angle )
		   v = -1; 
		}
		else 
		{
		 if (m_prevAngle2 < angle2 ) 
                   v = 1; 
		 if (m_prevAngle2 > angle2 )
                   v = -1; 
	        }

            int index = m_value / rRange; 
            int diff = m_inc - (m_value % rRange );
            if ( diff  < 0  && 1 == v )
              index ++;
            if (( diff > 0 )  && -1 == v )
              index --;

            //qDebug("m_inc %d  rRange %d, value %d, diff %d, v %d, index %d",m_inc,rRange,index*rRange + m_inc,diff, v, index);
            //qDebug("Value %d",value());
            m_value = index*rRange + m_inc; 

            if (m_rotationRange == maximum() - minimum()) 
            {
               if (m_value > maximum() - minimum()) 
                     m_value = m_inc ; 
               if (m_value < 0) 
                     m_value = maximum() - minimum() -rRange + m_inc ; 
            }

            else 
            {
            if (m_value > maximum() - minimum()) 
                 m_value = maximum() - minimum(); 
            }
            if ( -1 == v )
                emit valueDec(); 
            if ( 1 == v ) 
                emit valueInc(); 

            setValue(m_value + minimum() );
       }
        m_prevAngle2 = angle2;
        m_prevAngle = angle;
  }// Qt::LeftButton 
}// mouseMoveEvent 


void PotentioMeter::init()
{
    Q_INIT_RESOURCE(analogwidgets);
    m_renderer= NULL;
    m_rotationRange = 100; 
    m_value = value()-minimum();
    setRange(0,100);
    setSvgResourceFile(":/default/resources/dial1.svg"); 
}
