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

#include "chart/chartdecorator.h" 
 
using namespace chart;  
 /**
   * Operacja malowania. Zupe�nie abstrakcyjna. Ka�dy kolejny dekorator ma za zadanie domalowa�
   * kolejne elementy wykresu takie jak t�o, skala, siatka, sam wykres, legenda, inne rzeczy
   * Maluje kolejne elementy komponentu Chart.
   * @param painter Painter za pomoc� kt�rego ma odby� si� malowanie
   * @param chart   Wska�nik na g��wny komponent - pozwala wyd�bi� dodatkowe informacje
   */
   void ChartDecorator::paint (QPainter & painter, Chart * chart)
   {
     if (m_component) 
       m_component->paint(painter,chart);
   }
   
   /** 
   * Metoda kt�ra je�eli jest zaimplementowana zwraca pozycje absolutne dla 
   * pozycji kursora w ka�dym z kana��w ... je�eli nie ma kana��w to lista 
   * punkt�w absPoints jest pusta ... 
   * @param pos - Aktualna pozycja kursora na widgecie 
   * @param absPoints - Lista polo�e� absolutnych w kana�ach na podstawie pozycji position
   * @param chart - Wska�nik na chart'a by mo�liwe bylo dostanie si� do listy kana��w 
   * @param clip - Je�eli okienko by�o clipowane po drodze .. w�wczas podana jest jego pozycja 
   *               ko�cowa wzgl�dem okna g��wnego aplikacji 
   * UWAGA ... metod� t� powinny implementowa� wszystkie dekarotory kt�re zmieniaj� obszar 
   *           rysowania lub rysuj� bezpo�rednio dane. Te pierwsze modyfikatory powinny modifokowa�
   *           pole clip (domy�lnie takie samo jak ca�y widget) w taki spos�b by nawet podczas 
   *           wieloktornego clipowania ... clip wynikowy by� clipem wzg�dem ca�ego widgetu.
   *           Podobnie pozycja pos powinna by� modyfikowana w taki spos�b by by�a pozycj� 
   *           bezwzgl�dno� wobec clipu. 
   */
   void ChartDecorator::absPosition(QPoint & pos, QPolygonF & absPoints, Chart * chart,QRect & clip)
   {
      if (m_component) 
        m_component->absPosition(pos,absPoints,chart,clip);
   }

  /** Konstruktor - parametrem jest inny dekorator.*/
    ChartDecorator::ChartDecorator (ChartDecorator * component):m_component(component)
    {}

  /** Destruktor wirutalny */
   ChartDecorator::~ChartDecorator()
   {
    if (m_component) 
       delete m_component;
    m_component=0;
   }
