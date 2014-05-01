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
  			labelsdecorator.h - Copyright coder
**************************************************************************/

#ifndef LABELSDECORATOR_H
#define LABELSDECORATOR_H

#include "chart/chartdecorator.h"



namespace chart {
namespace Standard {
/**
 * Class LabelsDecorator
 * Klasa domalowywuj±ca etykiety do konkretnych wskazanych punktów na wykresie.
 */
class LabelsDecorator : public ChartDecorator {

public:

 /**
  * Konstruktor
  * @param component Pointer na nastêpny dekorator
  */
  LabelsDecorator (ChartDecorator * component ):ChartDecorator(component){}

 /** Operacja malowania. Maluje kolejne elementy komponentu Chart. */
  void paint (QPainter & painter, Chart * chart);

private:

};
} // chart
} // Standard
#endif //LABELSDECORATOR_H

