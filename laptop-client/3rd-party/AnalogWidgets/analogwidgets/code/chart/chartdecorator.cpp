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
   * Operacja malowania. Zupe³nie abstrakcyjna. Ka¿dy kolejny dekorator ma za zadanie domalowaæ
   * kolejne elementy wykresu takie jak t³o, skala, siatka, sam wykres, legenda, inne rzeczy
   * Maluje kolejne elementy komponentu Chart.
   * @param painter Painter za pomoc± którego ma odbyæ siê malowanie
   * @param chart   Wska¼nik na g³ówny komponent - pozwala wydêbiæ dodatkowe informacje
   */
   void ChartDecorator::paint (QPainter & painter, Chart * chart)
   {
     if (m_component) 
       m_component->paint(painter,chart);
   }
   
   /** 
   * Metoda która je¿eli jest zaimplementowana zwraca pozycje absolutne dla 
   * pozycji kursora w ka¿dym z kana³ów ... je¿eli nie ma kana³ów to lista 
   * punktów absPoints jest pusta ... 
   * @param pos - Aktualna pozycja kursora na widgecie 
   * @param absPoints - Lista polo¿eñ absolutnych w kana³ach na podstawie pozycji position
   * @param chart - Wska¼nik na chart'a by mo¿liwe bylo dostanie siê do listy kana³ów 
   * @param clip - Je¿eli okienko by³o clipowane po drodze .. wówczas podana jest jego pozycja 
   *               koñcowa wzglêdem okna g³ównego aplikacji 
   * UWAGA ... metodê t± powinny implementowaæ wszystkie dekarotory które zmieniaj± obszar 
   *           rysowania lub rysuj± bezpo¶rednio dane. Te pierwsze modyfikatory powinny modifokowaæ
   *           pole clip (domy¶lnie takie samo jak ca³y widget) w taki sposób by nawet podczas 
   *           wieloktornego clipowania ... clip wynikowy by³ clipem wzgêdem ca³ego widgetu.
   *           Podobnie pozycja pos powinna byæ modyfikowana w taki sposób by by³a pozycj± 
   *           bezwzglêdno± wobec clipu. 
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
