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

#ifndef DIAL_H
#define DIAL_H 
#include <QAbstractSlider> 
#include <QSvgRenderer> 

/**
  PotentioMeter is input widget designed to be used with touchscreens. It delivers 4 predefined themes 
  - Harman Kardon Potentiometer - dial1.svg
  - Matt steel Potentiometer    - dial2.svg
  - Plastic 1 Potentiometer     - dial3.svg
  - Plastic 2 Potentiometer     - dial4.svg 
  Feel free to add your own themes. To do that please follow id names in the svg files. 
*/ 
class PotentioMeter: public QAbstractSlider
{
   Q_OBJECT 
   Q_PROPERTY( int rotationRange READ rotationRange WRITE setRotationRange )
 public:
  PotentioMeter(QWidget * parent = NULL);

  int rotationRange() const;
  QString svgResourceFile() const;

  signals:
   void valueInc();
   void valueDec();
  public slots:
    /** 
        Sets ticks to rotation  if rotationRange is equal to maximum()- minimum() , widget
        is wraped. That allows to rotate dial many times 
     */
    void setRotationRange(int rotationRange); 

    /** Set resource file to alternative dial svg file */ 
    void setSvgResourceFile( const QString & filePath );

  protected: 
  void init(); 
  void paintEvent(QPaintEvent *);
  void mouseMoveEvent(QMouseEvent * event);

  qreal m_prevAngle,m_prevAngle2;
  int m_value;
  int m_rotationRange; 
  QString m_filePath; 
  QSvgRenderer * m_renderer;
};// PotentioMeter 
#endif // DIAL_H 
