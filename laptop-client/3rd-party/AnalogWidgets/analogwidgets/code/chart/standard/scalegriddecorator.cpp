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
  			scalesgriddecorator.cpp - Copyright coder
**************************************************************************/
#include <QtGui>
// #include <iostream>
#include "chart/standard/scalegriddecorator.h"
#include "chart.h"
#include "functions.h"

#define ACCURACY 0.000001 

using namespace std;
using namespace Standard;




/** Operacja malowania. Maluje kolejne elementy komponentu Chart. */
ScalesGridDecorator::ScalesGridDecorator (ChartDecorator * component )
  :ChartDecorator(component)
{
  scaleSize = 0.0;
  m_max = 1.0;
  m_min = 0.0;
  yScaleWidth = 0.0;
  yScaleHeight = 0.0; // jedna linia na samym dole 
}

void ScalesGridDecorator::paint (QPainter & painter, Chart * chart)
{
  painter.save();
  if (chart->doRepaintBackground())
  {  // to jest malowane na bitmapce w tle
     m_channelsScale = false; 
     paintBackground(painter,chart);
     paintYScale(painter,chart);
     paintYGrid(painter,chart);
  }
  else
  {  // a to ju¿ na samym ekranie
     paintXScale(painter,chart);
     paintXGrid(painter,chart);
       
     QRect r_clip(yScaleWidth,0,chart->width()-yScaleWidth,yScaleHeight); 
      //painter.setPen(Qt::green); 
     //painter.drawRect(r_clip);
     painter.setClipRect(r_clip); 
       
     QRect r_viewport(yScaleWidth,0,chart->width()-yScaleWidth,yScaleHeight); 
     //painter.setPen(Qt::cyan); 
     //painter.drawRect(r_viewport); 
     painter.setViewport(r_viewport);
  }
  //  painter.restore(); 
  ChartDecorator::paint(painter,chart);
 // painter.restore();
}

void ScalesGridDecorator::absPosition(QPoint & pos, QPolygonF & absPoints, Chart * chart,QRect & clip)
{
  // Tutaj nastêpuje modyfikacja pos oraz clip ... 
  clip = QRect((int)yScaleWidth,0,(int)(chart->width()-yScaleWidth),(int)yScaleHeight+1);
//  qDebug("Pozycja kursora przed %d,%d",pos.x(),pos.y()); 
  pos-=clip.topLeft(); 
//  qDebug("Pozycja kursora po %d,%d",pos.x(),pos.y()); 
  // By lecia³o dalej ... 
  ChartDecorator::absPosition( pos,absPoints,chart,clip); 
}


void ScalesGridDecorator::paintBackground(QPainter &painter, Chart * chart)
{
  QLinearGradient background(0,0,0,chart->height());
  background.setColorAt(0.0, chart->topBackgroundColor());
  background.setColorAt(1.0, chart->bottomBackgroundColor());
  painter.setBrush(QBrush(background));
  //painter.setBrush(Qt::black);
  painter.drawRect(0,0,chart->width(),chart->height());
}

#define XFONT_DISTANCE 7
#define YFONT_DISTANCE 2.5
void ScalesGridDecorator::paintYScale(QPainter & painter, Chart * chart)
{
  painter.setFont(chart->font());

  // wysoko¶æ skali X
   if (chart->scaleGrid().showScale)
   xScaleHeight = painter.fontMetrics().height()*2;
   else xScaleHeight = 0.0;
  // wysoko¶æ skali Y

   yScaleHeight = chart->height() - xScaleHeight;
  // szeroko¶æ skali Y

  int yMesh = chart->scaleGrid().m_yMesh;  // ilo¶æ lini na skali
  if (chart->scaleGrid().showScale)
   yScaleWidth=XFONT_DISTANCE;
  else yScaleWidth=0.0;

  Channels & channels = chart->channels();
  Channels::iterator i=channels.begin();
    
  if( !channels.empty() )
    while (i!=channels.end())
    {
    // @TODO - sprawdziæ czy warto¶ci przystaj± do skali  && if yMesh > 10 to sie dziwne rzeczy dzieja 
    int maxTextWidth=0; // maksymalna szeroko¶æ napisu skali
    
    m_channelsScale |=i->showScale(); // czy który kolwiek kana³ ma mlowan± skalê 
    
    // To musi byæ wiloczone bez wzgêdu czy jest rysowana skala czy nie 
    // bo jest to potrzebne do rysowania samych wykresów 
    double m_min,m_max;
    range(i->minimum(),i->maximum(),m_min,m_max,yMesh,true,minimalStep(i->maximum()-i->minimum(),yMesh));  // wyznaczenie ca³ej rangi ...
    double scaleStep = (m_max-m_min)/ yMesh;
    i->setCalcMinMax(m_min, m_max+scaleStep); //  ustawianie wymiarów dla kana³ów
    
    if (i->showScale())
    {
      painter.setPen(i->pen());
      double scalePos=m_max;
      double posStep = yScaleHeight /( yMesh+1), posText=posStep;
      // malowanie literek skali
      while ( scalePos + ACCURACY >  m_min )
      {
        if (fabs(scalePos)<ACCURACY ) scalePos = 0.0; // brzydki hack ale pownien dzia³aæ.
        if (fabs(scalePos) <  0.000000000001 ) scalePos = 0.0; 		
        QString Str = QString().setNum(scalePos,'G',12); // "%1").arg(scalePos,6);
        int tw = painter.fontMetrics().size(Qt::TextSingleLine, Str ).width();
        if (tw>maxTextWidth) maxTextWidth=tw;
        painter.drawText(QPointF(yScaleWidth,posText-YFONT_DISTANCE),Str);
        posText+=posStep;
        scalePos-=scaleStep;
      }
      
      yScaleWidth+=XFONT_DISTANCE+maxTextWidth;
    }// if showScale
      i++; 
    }// while i!=channels.end()
}




void ScalesGridDecorator::paintXScale(QPainter & painter, Chart * chart)
{
   int xMesh = chart->scaleGrid().m_xMesh;
   double pos = chart->scaleGrid().pos;
   
   if (scaleSize != chart->scaleGrid().size )
   {
     scaleSize = chart->scaleGrid().size;
     range(0.0,scaleSize,m_min,m_max,xMesh,true,minimalStep(scaleSize,xMesh));
     // Absolutna pozycja ...
//     chart->scaleGrid().m_min = m_min + pos;
//     chart->scaleGrid().m_max = m_max + pos;
   }


     double scale_step = (m_max - m_min) / (xMesh);
     //cout<<"Scale Step="<<scale_step<<endl; 
     
     double factor = (chart->width() - yScaleWidth )/ scaleSize;
     double start_pos = - fmod(pos,scale_step); // by rozpocz±³ od pocz±tku
     double scale_pos = start_pos * factor;

     painter.setFont(chart->font());
     painter.setPen(chart->scaleGrid().m_pen); //kolor fontu

     double scale_value_step = ( m_max - m_min ) / xMesh;
     double scale_value=pos - fmod(pos,scale_value_step);
     //cout<<"Pos:"<<pos <<" fmod:"<<fmod(pos,scale_value_step);
     //cout<<" scale_number:"<<scale_value<<" scale_number_step:"<<scale_value_step<<endl;
     chart->scaleGrid().m_min = m_min + pos;
     chart->scaleGrid().m_max = pos + scaleSize;

    if (chart->scaleGrid().showScale)
   {
    int x,y,fw;
    do
    {
      y = (chart->height()- static_cast<int>(yScaleHeight));
      //  painter.drawLine(QPointF(scale_pos,yScaleHeight + y*0.25 ),QPointF(scale_pos,yScaleHeight));
      if (fabs(scale_value) <  0.000000000001 ) scale_value = 0.0; 		
      QString Str = QString().setNum(scale_value,'G',12); ////QString("%1").arg(scale_value,6);
      fw = painter.fontMetrics().size(Qt::TextSingleLine, Str ).width();
      x = static_cast<int> (scale_pos - fw/2 + yScaleWidth);
      if (x + fw/2 >= yScaleWidth )
      painter.drawText(QPointF(x ,yScaleHeight+y*0.6+YFONT_DISTANCE),Str);
      scale_pos+=scale_step * factor;
      scale_value+=scale_value_step;

      start_pos += scale_step;
    }while (x <= chart->width() ) ;
    
    // Pozioma lina nad skal± .
    painter.setPen(chart->gridColor()); 
    painter.drawLine(QPointF(0,yScaleHeight),QPointF(chart->width(),yScaleHeight));
   } // if showScale

}

void ScalesGridDecorator::paintXGrid(QPainter & painter, Chart * chart)
{ 
  painter.setPen(chart->gridColor()); // kolor siatki
  
  if (chart->scaleGrid().showGrid || chart->scaleGrid().showScale) 
  {
     int xMesh = chart->scaleGrid().m_xMesh;
     double pos = chart->scaleGrid().pos;

     // scaleSize = chart->scaleGrid().size; - jako zmienna klasy
     //range(0.0,scaleSize,m_min,m_max,xMesh,true,minimal_step);
     double scale_step = (m_max - m_min) / (xMesh);

     double factor = (chart->width() - yScaleWidth )/ scaleSize;
     double start_pos = - fmod(pos,scale_step);
     double scale_pos = yScaleWidth + start_pos * factor;
    
    

     int xSubMesh = chart->scaleGrid().m_xSubMesh +1;
     int y;
     
     double ScaleBottom = 0.0 ;// czy bêd± d³ugie kreski czy tylko pici pici przy liczbach 
     
     if (!chart->scaleGrid().showGrid)
        ScaleBottom = yScaleHeight;
     else // linia pionowa zamykajaca siatkê od prawej  
        painter.drawLine ( QPoint(chart->width()-1,0),QPoint(chart->width()-1,(int)yScaleHeight));
     
     do
     {
      //painter.drawLine(QPointF(scale_pos,0),QPointF(scale_pos,yScaleHeight));

       y = (chart->height()- static_cast<int>(yScaleHeight) );
       if (scale_pos>=yScaleWidth)
       painter.drawLine(QPointF(scale_pos,yScaleHeight + y*0.25 ),QPointF(scale_pos,ScaleBottom));
       for (int i=-xSubMesh;i<xSubMesh;i++)
       {
         double scale_sub_step = scale_step / xSubMesh;
         double xSub = scale_pos+scale_sub_step*i*factor;
         if (xSub>yScaleWidth) painter.drawLine(QPointF(xSub,yScaleHeight),QPointF(xSub,ScaleBottom));
       }

       scale_pos+=scale_step * factor;
     }while (scale_pos <= chart->width() ) ;
    
  }// if showScale or Grid    
}

void ScalesGridDecorator::paintYGrid(QPainter & painter, Chart * chart)
{
  painter.setPen(chart->gridColor());

  // Malowanie lini poziomych
  unsigned int ySteps    = chart->scaleGrid().m_yMesh + 1;
  unsigned int ySubSteps = 1;
  double       length    = yScaleWidth;

  if ( chart->scaleGrid().showGrid && ySubSteps)
   {
      length = chart->width();
      ySubSteps = chart->scaleGrid().m_ySubMesh + 1;
   }

 double step   = yScaleHeight/(ySteps*ySubSteps);
 double pos = 0.0;

  for (unsigned int i=0;i<ySteps*ySubSteps;i++)
  {
    if (i%ySubSteps)  // je¿eli s± ustawione
        painter.drawLine(QPointF(yScaleWidth,pos),QPointF(length,pos));
    else
        painter.drawLine(QPointF(0.0,pos),QPointF(length,pos));
    pos+=step;
  }
   // pionowa linia po lewej otwieraj±ca skalê lub ca³± siatkê 
   if (m_channelsScale || chart->showGrid() || chart->showScale() )
   painter.drawLine(QPointF(yScaleWidth,0.0),QPointF(yScaleWidth,yScaleHeight));
  
  // Jezeli nie ma skali a jest siatka to malujemy tez line na samym dole 
  if (chart->scaleGrid().showGrid && !chart->scaleGrid().showScale) 
   painter.drawLine(QPoint(0,chart->height()-1),QPoint(chart->width(),chart->height()-1)); 

}

