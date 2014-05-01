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

#ifndef TEST_H
#define TEST_H

#include "ui_testform.h"

#include <QMainWindow>

    class ManoMeter;
    class ThermoMeter;
    class Chart;


    class TestWidget : public QMainWindow,  private Ui::TestForm
    {
    	Q_OBJECT
    public:
        TestWidget(QMainWindow *parent = 0);
        /** Inicjuje podstawow± geometriê oraz komponenty na formie */
        void initialize();
        
        /** Inicjuje wykres */ 
        void initCharts(); 
        
        /** Generuje p³±czenia pomiêdzy sygna³ami i slotami */
        void connections();
    public slots:
    	void ComboBoxChoiceChanged(int index );
        void SpinBoxValueChanged(int val);
	void WidgetTest();
        void tabChange(int i);
	void movePosition(int val);
	void setSize(int val);
	void loadInjection(const QString &  file );


    private:
	/** Gdy zamykane jest okno */
	void closeEvent ( QCloseEvent * e );
        /** Wczytuje dane przyk³adowego wtrysku i pokazuje je na wykresie */


	// Potencjometr
	ManoMeter * bar;
	// Termometr
	ThermoMeter * thermo;
	// Wykres
 	Chart * chart;
    };





#endif // TEST_H
