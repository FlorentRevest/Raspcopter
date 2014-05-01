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
  			legenddecorator.cpp - Copyright coder
**************************************************************************/
#include <QtGui>
#include <cmath>
#include "chart/standard/legenddecorator.h"
#include "chart.h"

using namespace std;
using namespace Standard;

/** Operacja malowania. Maluje kolejne elementy komponentu Chart. */

void LegendDecorator::paint (QPainter & painter, Chart * chart)
{
 
 if (!chart->doRepaintBackground())
  if (chart->isPaintOver())
  if (chart->showLegend()) 
  {
    unsigned int rh = painter.renderHints();
    painter.setRenderHint(QPainter::RenderHint(0x0)); // w³aczenie antialiasingu

    paintLegendFrame(painter,chart);

    painter.setRenderHint(QPainter::RenderHint(rh)); // wylaczenie antialiasingu
  }// if isPaintOver
  ChartDecorator::paint(painter,chart); // uruchomienie nastêpnego dekoratora
}

#define XOFFSET 10
#define YOFFSET 10
#define RIGHTOFFSET 15
#define TOPOFFSET 15
void LegendDecorator::paintLegendFrame(QPainter & painter, Chart * chart)
{

    Channels & channels = chart->channels();
    Channels::iterator i=channels.begin();
    int width=0,height=0;
    QSize size;
    // Wyliczenie rozmiarów maksymalnych ramki
    painter.setFont(chart->font());
    while (i!=channels.end())
    {
      size = painter.fontMetrics().size(Qt::TextSingleLine, i->name());
      width = max(width,size.width());
     if (i->visible() && i->showLegend()) 
      height += size.height();
     i++; 
    } // while
    
    if (0 == height) // nic nie ma do pokazania 
      return; 
    // Utworzenie gradientu oraz innych niezbednych pedzli i szczotek :)
    QLinearGradient gradient(0,0,0,(height+2*XOFFSET+TOPOFFSET)/2);
    gradient.setSpread(QGradient::ReflectSpread);
    gradient.setColorAt(1.0,QColor(50,150,90,150));
    gradient.setColorAt(0.0,QColor(0,150,150,150));
    painter.setBrush(gradient);
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidthF(1.5);
    painter.setPen(pen);
    int x = width + 2*XOFFSET + RIGHTOFFSET;
    int y =  TOPOFFSET;
    // Namalowanie ramki z t³em
    painter.drawRoundRect(chart->width() - x, y, width+XOFFSET*2,height+YOFFSET,9,18);

    // Malowanie napisów z opisami
    i = channels.begin();
    x = chart->width() - x + XOFFSET;
    y = TOPOFFSET + YOFFSET*2;
    while (i!=channels.end())
    {
      if (i->visible() && i->showLegend())
      {
        size = painter.fontMetrics().size(Qt::TextSingleLine, i->name());
        painter.setPen(i->pen());
        painter.drawText(x,y,i->name());
        y += size.height();        
      }
      ++i; 
    } // while
}

