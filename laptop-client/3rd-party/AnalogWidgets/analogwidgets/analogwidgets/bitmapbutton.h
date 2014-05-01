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

#ifndef BITMAPBUTTON_H
#define BITMAPBUTTON_H

#include <QAbstractButton>
#include <QIcon> 
#include <QTimer> 


/** Two stat bitmap buttom may be used for touch screen keyboard button  */
class BitmapButton: public QAbstractButton
{
  Q_OBJECT
  Q_PROPERTY (QIcon downIcon READ downIcon WRITE setDownIcon)    

  public:
      BitmapButton(QWidget * parent = 0);
      ~BitmapButton(); 
      QIcon downIcon() const ;
      void setDownIcon(const QIcon & icon);

  protected slots:


  protected: 
    
  void init();
  virtual void paintEvent ( QPaintEvent * event );

  QIcon m_downIcon;

}; // BitmapButton

#endif // BITMAPBUTTON_H

