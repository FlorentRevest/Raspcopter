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

#include "chart/channel.h"

using namespace chart;

Channel::Channel()
{
   m_min= m_calc_min= 0;
   m_max= m_calc_max= 450;
   m_showScale=true;
   m_visible = true; 
   m_showLegend = true;
   m_pen.setColor(Qt::white);
   m_data = NULL;
   m_type = Line; 
  // m_iterator_begin=m_iterator_end=0; // wska¼nik na NULL
}

Channel::Channel(double min,double max, ChannelData * data,QString name,QPen pen )
{
  this->m_min = m_calc_min = min;
  this->m_max = m_calc_max = max;
  this->m_data = data;
  this->m_name = name;
  this->m_pen = pen;
  m_showScale = true;
  m_visible = true;
  m_showLegend =true; 
  m_type = Line;  
}


Channel::~Channel()
{
 ;// if (m_data) 
 ; //   delete m_data;  
}

void Channel::setPen(const QPen & pen)
{
  m_pen = pen;
}

QPen Channel::pen() const
{
  return m_pen; 
}
   
void Channel::setName(const QString & name)
{
  m_name = name;  
}
   
QString Channel::name() const
{
  return m_name; 
}
  
ChannelData * Channel::data() const
{
  return m_data;  
}
   
 
double Channel::maximum() const 
{
  return m_max ; 
}


void Channel::setMaximum(double i) 
{ 
   if (i>m_min) 
      m_max = i;
}


double Channel::minimum() const 
{ 
  return m_min ; 
}


void Channel::setMinimum(double i) 
{ 
  if (i<m_max) 
    m_min = i;
}
   
   
void Channel::setCalcMinMax(double a,double b)
{
  if (a<b)
  {
    m_calc_min = a; 
    m_calc_max = b; 
  }
}


void Channel::getCalcMinMax(double &a, double &b)
{
  a = m_calc_min; 
  b = m_calc_max ; 
}
   
   
bool Channel::showScale() const 
{ 
  return m_showScale; 
}


void Channel::setShowScale(bool i)
{ 
  m_showScale = i ; 
} 


bool Channel::visible() const
{
  return m_visible; 
}

void Channel::setVisible(bool i)
{
  m_visible = i; 
}

bool Channel::showLegend() const 
{
  return m_showLegend;
}

void Channel::setShowLegend(bool i) 
{
  m_showLegend = i;  
}

void Channel::setType(unsigned int i)
{
  if (i!=Line && i!=Dots)
   throw "Bledny typ"; 
     
  m_type = i; 
  
}

unsigned int Channel::type()
{
  return m_type;  
}
