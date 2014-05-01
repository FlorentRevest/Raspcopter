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

    #include "test.h"
    #include <QFont>
    #include <QPushButton>
    #include <QSlider>
    #include <QString>
    #include <QTimer>
#include <QFile>
#include <QTextStream>


    #include "manometer.h"
    #include "wallclock.h"
    #include "thermometer.h"
    #include "chart.h"
    #include "chart/datacontainers.h"
    #include "potentiometer.h" 


    #include "widgettester.h"

    #include <iostream>
    #include <fstream>
    #include <list>
    #include <vector>
    
     #define UNDEPRESS "[bar] Press 1"
     #define CALCPRESS "[bar] Press 2"
     #define OVERPRESS "[bar] Press 3"


    using namespace std;

    typedef vector<int> vint;
    typedef list <int>  lint;
    typedef list <double> ldouble;
    typedef list< pair<double,double> > lpair;

    lpair position;
    vint  velocity;
    vint  times;
    lint  press1;
    lint  press2;
    ldouble press3;

// ----------------------------------------------------------------------------------------

    TestWidget::TestWidget(QMainWindow *parent)
        : QMainWindow(parent)
    {
        initialize ();
 	connections();
    }

    void TestWidget::initialize()
    {
      setupUi(this);
      //setWindowTitle(QString("Program testowy dla AnalogWidgets"));
      setWindowFlags(Qt::Window);
      setGeometry(50,50,400, 320);

        // Ustawianie LayOut'ów
        QWidget * widget = stackedWidget->widget(0);
        // Layout of stack 0 widget
        WallClock * clock = new WallClock();
        QVBoxLayout *v_layout = new QVBoxLayout;
        v_layout->addWidget(clock);
        widget->setLayout(v_layout);

         // Layout of stack 1 widget - manometer

        widget = stackedWidget->widget(1);
        bar = new ManoMeter(widget);
        bar->setValueFont(font()); // bar->digitFont());
        bar->resize(120,120);
        QLayout * layout = new QVBoxLayout();
        layout->addWidget(bar);
        widget->setLayout(layout);

        // Layout if stack 2 widget - thermometer

        widget = stackedWidget->widget(2);
        thermo = new ThermoMeter();
        thermo->resize(10,100);
        QLayout * layout2 = new QVBoxLayout();
        layout2->addWidget(thermo);
        widget->setLayout(layout2);

        // Layout of - chart
        widget = stackedWidget->widget(5);
        chart = new Chart();
        QLayout * layout3 = new QVBoxLayout();
        layout3->addWidget(chart);
        QLayout * wert = new QHBoxLayout(); 
        wert->addWidget(chartPosition); 
        wert->addWidget(zoomBox); 
        layout3->addItem(wert);
        layout3->addWidget(sizeSlider);
        layout3->addWidget(injCombo);
        widget->setLayout(layout3);

        
        layout = new QVBoxLayout(); 
        PotentioMeter * m_dial = new PotentioMeter();
        QComboBox * dialCombo = new QComboBox(); 
        layout->addWidget(m_dial);
        layout->addWidget(dialCombo); 
        dialCombo->addItem(":/default/resources/dial1.svg"); 
        dialCombo->addItem(":/default/resources/dial2.svg"); 
        dialCombo->addItem(":/default/resources/dial3.svg"); 
        dialCombo->addItem(":/default/resources/dial4.svg"); 
        dialCombo->addItem(":/test/resources/volume.svg"); 

        connect(dialCombo,SIGNAL(activated ( const QString & )),m_dial,SLOT(setSvgResourceFile( const QString & ))); 
         
        connect(HSlider,SIGNAL(valueChanged(int)),m_dial,SLOT(setValue(int))); 
        potentiometer_tab->setLayout(layout); 
        // za³adowanie listy wtrysków do CobmboBox'a
        QDir dir(":/test/wtr");
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        dir.setNameFilters ( QStringList(QString("*.wtr")) );
        injCombo->addItems(dir.entryList());
        
        //connect(HSlider,SIGNAL(valueChanged(int)),bar,SLOT(setValue(int)));
        //connect(spinBox,SIGNAL(valueChanged(int)),bar,SLOT(setValue(int)));
        connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(SpinBoxValueChanged(int)));
        connect(comboBox,SIGNAL(activated(int)),this,SLOT(ComboBoxChoiceChanged(int)));
        connect(pushButton,SIGNAL(clicked(void)),this,SLOT(WidgetTest(void)));
        connect(chartPosition,SIGNAL(valueChanged(int)),this,SLOT(movePosition(int)));
        connect(sizeSlider,SIGNAL(sliderMoved(int)),this,SLOT(setSize(int)));
        connect(injCombo, SIGNAL(activated( const QString & )), this,SLOT(loadInjection(const QString& ))) ;
        connect(zoomBox,SIGNAL(valueChanged(double)),chart,SLOT(setZoom(double))); 
        HSlider->setMaximum(1000);
        HSlider->setMinimum(-1000);
        spinBox->setMaximum(1000);
        spinBox->setMinimum(-1000);
        ComboBoxChoiceChanged(comboBox->currentIndex());

        connect(stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChange(int)));

    }
    
    void TestWidget::initCharts()
    {
     // Zainicjowanie danymi obiektu typu chart

      QPen vPen;
      vPen.setColor(Qt::red);
      vPen.setWidthF(2.0);
      vPen.setColor(Qt::green);
      Channel cisnienie2 (0,350,new DoubleDataContainer<vint,lint>(times,press2),
                          trUtf8(UNDEPRESS),vPen);
      vPen.setColor(Qt::magenta);
      Channel cisnienie3 (0,350,new DoubleDataContainer<vint,ldouble>(times,press3),
                          trUtf8(CALCPRESS),vPen);
      vPen.setColor(Qt::cyan);
      Channel cisnienie (0,350,new DoubleDataContainer<vint,lint>(times,press1),
                         trUtf8(OVERPRESS),vPen);
      vPen.setColor(Qt::yellow);
      Channel pozycja(0,230,new PairDataContainer<lpair>(position),
                      trUtf8("[mm] Pozycja"),vPen);
/*	//vPen.setStyle(Qt::DashDotLine);
      vPen.setColor(Qt::red);
      Channel predkosc  (0,300, new DoubleDataContainer<vint,vint>(times,velocity),
                         trUtf8(VELOCITY),vPen) ;//QPen(Qt::red));

*/
      cisnienie2.setShowScale(false); 
      cisnienie3.setShowScale(false);
	//pozycja.showScale = predkosc.showScale = false ;
	//chart->scaleGrid().showScale=false;
	//chart->scaleGrid().showGrid=false;
      chart->addChannel(cisnienie2);
      chart->addChannel(cisnienie3);
      chart->addChannel(cisnienie);
  //    chart->addChannel(pozycja);
  //    chart->addChannel(predkosc);
 
    }

    void TestWidget::movePosition(int val)
    {
      chart->setPosition(val);
    }
    void TestWidget::setSize(int val)
    {
      chart->setSize(val);
    }

    void TestWidget::ComboBoxChoiceChanged(int index)
    {
      int val=0;
      AbstractMeter * meter = bar;
      if (stackedWidget->currentIndex() == 2) meter = thermo;

      switch (index)
      {
       case 0: val = static_cast<int> ( meter->value()); break;
       case 1: val = static_cast<int> (meter->minimum()); break;
       case 2: val = static_cast<int> (meter->maximum()); break;
       case 3: val = static_cast<int> (meter->nominal()); break;
       case 4: val = static_cast<int> (meter->critical()); break;
       case 5: val = static_cast<int> (meter->digitOffset()); break;
       case 6: val = static_cast<int> (meter->valueOffset()); break;
      }
       spinBox->setValue(val);
    }

    void TestWidget::SpinBoxValueChanged(int val)
    {
      AbstractMeter * meter = bar;
      if (stackedWidget->currentIndex() == 2) meter = thermo;

      switch (comboBox->currentIndex())
      {
        case 0:  meter->setValue(val); break;
        case 1:  meter->setMinimum(val); break;
        case 2:  meter->setMaximum(val); break;
        case 3:  meter->setNominal(val); break;
        case 4:  meter->setCritical(val); break;
        case 5:  meter->setDigitOffset(val); break;
        case 6:  meter->setValueOffset(val); break;
      }
    }
    void TestWidget::WidgetTest()
    {
	AbstractMeter * meter;
	switch (stackedWidget->currentIndex())
	{
	  case 1: meter = bar; break;
	  case 2: meter = thermo;break;
	  default: meter = NULL ; return;
        }
	WidgetTester * tester = new WidgetTester(this,meter);
	tester->start();
    }

    void TestWidget::tabChange(int i)
    {
        frame->setVisible(i!=5);
    }

    void TestWidget::connections()
    {


    }

  void TestWidget::loadInjection(const QString &  file )
    {


        QString f(":/test/wtr/");

         f+=file;
        QFile filein(f);
        if (!filein.open(QFile::ReadOnly))
          qDebug("Nie udane otwarcie pliku: %s",qPrintable(file)); 
         

/*	for (int i=0;i<11;i++)
        {
           filein.getline(buffer,1023,'\n'); // pominiecie nag³ówka
           //cout<<buffer<<endl;
         }
 */
        double /*pos, vel,*/p1,p2,p3;
	times.clear(); // vint
//	velocity.clear(); // vint
 	press1.clear(); // vint;
        press2.clear();
	press3.clear();
//	position.clear(); //lpair
        int time = 0;

        QTextStream stream(&filein);

        while (!filein.atEnd())
        {
          ///stream>>pos;
          stream>>p3;
          stream>>p1;
          stream>>p2;
          //qDebug("Strem %f,%f,%f",p1,p2,p3);
          stream.readLine() ; // getline(buffer,1023,'\n'); // eat rest of the line
    //      filein>>vel;
          times.push_back(time);
         // position.push_back( pair<double,double>(time,pos));
	//  velocity.push_back((int)vel);
	  press1.push_back((int)p1);
	  press2.push_back((int)p2);
	  press3.push_back(p3);


          //filein>>buffer;
         // cout<<time<<"  p:"<<pos<<" v:"<<vel<<" p1:"<<p1<<endl; //" "<<p2<<" "<<p3<<endl;
	  ++time;
        }
        
        
        chart->channels().clear(); 
        initCharts(); 
        chart->update();
    }

    void TestWidget::closeEvent ( QCloseEvent * /* event */)
    {
      qApp->quit();
    }
