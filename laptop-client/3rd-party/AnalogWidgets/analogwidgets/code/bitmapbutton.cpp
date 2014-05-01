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
#include "bitmapbutton.h" 

#define TIMERCYCLES 5
BitmapButton::BitmapButton(QWidget * parent):QAbstractButton(parent)
{
}

BitmapButton::~BitmapButton()
{
   ;
}


QIcon BitmapButton::downIcon() const 
{
  return m_downIcon; 
}

void BitmapButton::setDownIcon(const QIcon & icon)
{
  m_downIcon = icon; 
}

void BitmapButton::paintEvent ( QPaintEvent *  )
{
  QPainter painter(this);
   QIcon *  p_icon, tmp = icon();  
   if( isDown() || isChecked())
     	p_icon = &m_downIcon;
   	//m_downIcon.paint(&painter,0,0,width(),height());
     else 
        p_icon = &tmp;
        // icon().paint(&painter,0,0,width(),height());
   
	QSize aSize = p_icon->actualSize(size()); 
	painter.drawPixmap(QRect(0,0,width(),height()),
			   p_icon->pixmap(aSize)
			   ,QRect(0,0,aSize.width(),aSize.height())
			   );
}

