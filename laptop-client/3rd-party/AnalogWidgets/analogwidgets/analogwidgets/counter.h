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

#ifndef COUNTER_H
#define COUNTER_H 

#include <QWidget> 
#include <QString> 


class QSvgRenderer; 
/**
  Counter shows counter with digits taken from input svg file. 
  Feel free to add your own themes. To do that please follow id names int svg file.
*/

class Counter: public QWidget
{
 Q_PROPERTY (int value READ value WRITE setValue) 
 Q_PROPERTY (int digits READ digits WRITE setDigits)

 Q_OBJECT
  public:
  Counter (QWidget * parent = NULL); 

  int digits() const;
  int value() const;
  const QString digitsFile() const; 
  public slots: 

  void setValue(int);
  void setDigits(int);

  /** Sets filepath to svg file with digits */ 
  void setDigitsFile(const QString & ); 

  protected:
   void paintEvent (QPaintEvent *);
   void init();

   int m_digits;
   int m_value;
   QString m_digitsFile;
   QSvgRenderer * m_svg;

}; // class Counter 
#endif // COUNTER_H 
