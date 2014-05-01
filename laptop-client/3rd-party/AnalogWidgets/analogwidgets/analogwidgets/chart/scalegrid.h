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
  			scalegridproperties.h - Copyright coder
**************************************************************************/

#ifndef SCALEGRIDPROPERTIES_H
#define SCALEGRIDPROPERTIES_H

#include <QPen>
#include <QFont>

namespace chart {
/** Struktura zawieraj�ca dane na temat skali oraz siatki */
class ScaleGrid {

public:
   /** Zastosowany font skali */
   //QFont m_font;
   //QColor m_fontColor;
   /** Rodzaj u�ytego pi�ra do rysowania skali siatki oraz kolor */
   QPen m_pen;


   /** Ilo�� pionowych "drut�w" w siatce wykresu */
   unsigned int  m_xMesh;
   /** Ilo�� poziomych "drut�w" w siatce wykresu */
   unsigned int m_yMesh;
   /** Ilo�� pionowych "pod-drut�w" w siatce wykresu */
   unsigned int m_xSubMesh;
   /** Ilo�� poziomych "pod-drut�w" w siatce wykresu */
   unsigned int m_ySubMesh;
  /** Minimalna warto�� na skali */
   double pos;
  /** Maksymalna warto�� na skali*/
   double size;
 
	   /** minimalna wy�wietlana warto�� na skali */
   	   	double m_min;
	   /** Maksymalna wy�wietlana warto�� na skali */
   		double m_max;

  /** Czy ma by� narysowana siatka dla ca�ej skali */
   bool showGrid;

  /** Czy ma pokazac skale */
   bool showScale;
  /** Konstruktor domy�lny */
  ScaleGrid ( );

};
} // namespace chart
#endif //SCALEGRIDPROPERTIES_H

