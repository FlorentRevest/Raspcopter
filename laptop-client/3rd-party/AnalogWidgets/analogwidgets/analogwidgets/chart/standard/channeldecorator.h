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

/************************************************************************
  			channeldecorator.h - Copyright coder
**************************************************************************/

#ifndef CHANNELDECORATOR_H
#define CHANNELDECORATOR_H

#include "chart/chartdecorator.h"



namespace chart {
namespace Standard {
/**
 * Class ChannelDecorator
 * Implementacja rysowania kana��w z danymi dla komponentu Chart
 */
class ChannelDecorator :  public ChartDecorator 
{
  
public:

  /**
  * Konstruktor
  * @param component Pointer na nast�pny dekorator
  */
  ChannelDecorator (ChartDecorator * component ):ChartDecorator(component){}

  /** Operacja malowania. Maluje kolejne elementy komponentu Chart. */
   void paint (QPainter & painter, Chart * chart);
   
  /** 
  * Podaje pozycje absolutne w kt�rych (w kana�ach) znajduje si� krusor (odczytan� z wykresu) 
  * @see ChartDecorator::absPosition 
  */ 
 void absPosition(QPoint & pos, QPolygonF & absPoints, Chart * chart,QRect & clip);
  
private:
   /** Wyskalowywuje uk�ad rysowania do wieko�ci danych w kanale */
   void translateToChannel (QPainter & painter, Chart * chart, Channel & channel);
   /** Rysuje dane z kana�u */
   void paintChannel(QPainter & painter,Chart * chart, Channel & channel);

   double xfactor;
   double yfactor;
   double dx,dy;
   // Szeroko�� okienka 
   double dxw; 
   // Wielko�� okienka ... 
   QRect window; 
   // Wielko�� viewportu 
   QRect viewport; 

};// class ChannelDecorator
} // chart
} // Standard
#endif //CHANNELDECORATOR_H

