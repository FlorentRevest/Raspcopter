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

#include <QtGui>
#include <cmath>
#include <assert.h>
#include "thermometer.h"

using namespace std;
ThermoMeter::ThermoMeter(QWidget *parent)
        : AbstractMeter(parent)
{
        m_max=80;
        m_min=0;

	m_maximum=80; // najpierw rêcznie potem seterem by wywo³aæ calcMaxMin
  	setMinimum(0);
	setValue(0);
        setNominal(30);
	calcMaxMin(); // bo nie wiemy czym s± zainicjowane limity
	setCritical(60);
	setValueOffset(270);
	setDigitOffset(10);
	setSuffix(QString(" [C]"));
	m_digitFont.setPointSize(15);
	m_valueFont.setPointSize(18);

	// QWidget
        setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(tr("Analog Thermometer"));
	resize(200, 200);
	assert(m_max-m_min != 0);

}

void ThermoMeter::initCoordinateSystem(QPainter & painter)
{
        // inicjalizacja paintera
        painter.setRenderHint(QPainter::Antialiasing);
        //painter.translate(width() / 2, height() / 2);
        painter.translate( width()/2.0,0.0);
        painter.scale( height()/ 300.0, height()/307.0);
}

void ThermoMeter::paintBackground(QPainter & painter)
{
	initCoordinateSystem(painter);
	// kszta³t szkalnej bañki

	QPainterPath glass;

	// pocz±tek ³uku dolnego po lewej stronie
	glass.moveTo(12.5,267.5);
	glass.quadTo(12.5,263.0, 7.5,257.0);

	glass.lineTo(7.5,25.0);

	// ³uk górny zamykajac5y bañkê od góry.
	glass.quadTo(7.5,12.5 , 0,12.5);
	glass.quadTo(-7.5,12.5,-7.5,25.0);
	glass.lineTo(-7.5,257.0);
	// tutaj musi byæ ³uk dolny o promineniu 25
	glass.quadTo(-12.5,263.0, -12.5,267.5);
	glass.quadTo(-12.5,278.0,  0.0,280.0);
	glass.quadTo( 12.5,278.0,  12.5,267.5);

        QLinearGradient linearGrad(QPointF(-2.0, 0.0), QPointF(12.5, 0.0));
	linearGrad.setSpread(QGradient::ReflectSpread);
        linearGrad.setColorAt(1.0, QColor(0,150,255,170));
        linearGrad.setColorAt(0.0, QColor(255,255,255,0));

	painter.setBrush(QBrush(linearGrad));
	painter.setPen(Qt::black);
	painter.drawPath(glass);

	/*
	QRadialGradient radial(0.0,267.5,12.5,-10.0,263.0);
	radial.setColorAt(1.0,QColor(0,150,255,110));
	radial.setColorAt(1.0,QColor(255,255,255,0));
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(QRectF(-12.5,255.0,25.0,25.0));
	*/
	QPen pen;
	int length = 12;
	for (int i=0;i<=32;i++)
	{
	  pen.setWidthF(1.0);
	  length = 12;
	  if (i%4) { length = 8; pen.setWidthF(0.75); }
	  if (i%2) { length = 5; pen.setWidthF(0.5);  }
	  painter.setPen(pen);
	  painter.drawLine(-7,28+i*7, -7+length,28+i*7);
	}

	if (digitOffset())
        {
          painter.setFont(digitFont());
	  for (int i=0;i<9;i++)
	  {
	    QString val = QString("%1").arg(m_min + i*(m_max - m_min)/8.0 );
	    QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, val);

	    painter.drawText( QPointF( digitOffset(),252 -  i * 28 +Size.width()/4.0) , val);

	  }
	}


}// paintBackground

// Offset by lepiej by³o widaæ o co z nim biega - mówi±c oglêdnie offset to miejsce
// poni¿ej zera od którego zaczynamy rysowaæ s³upek rtêci.
#define OFFSET 10

void ThermoMeter::paintEvent(QPaintEvent * )
{
      // Inicjalizacja paintera
	QPainter painter(this);
        initCoordinateSystem(painter);
      // --------------------------------------------- ///
       // Dobór colorów do rysowania
	QColor color=Qt::blue;
	if (m_value >= m_nominal )
	    color=QColor(0,200,0);

	if (m_value >= m_critical)
	   {
		color=Qt::red;
	     	painter.setPen(color); // by potem temp podaæ na czerwono
	   }

	if (valueOffset())
	{
	  painter.setFont(valueFont());
          QString Str = prefix() + QString("%1").arg(value()) + suffix();
          QSize Size = painter.fontMetrics().size(Qt::TextSingleLine, Str);
          painter.drawText(QPointF (Size.width() / -2,valueOffset() + Size.height()) , Str);
	}


	QLinearGradient slupek(0.0,0.0,5.0,0.0);
	QRadialGradient zbiornik(0.0,267.0,10.0,-5.0,262.0);

	slupek.setSpread(QGradient::ReflectSpread);
	zbiornik.setSpread(QGradient::ReflectSpread);

	color.setHsv(color.hue(),color.saturation(),color.value());
	slupek.setColorAt(1.0,color);
	zbiornik.setColorAt(1.0,color);

	color.setHsv(color.hue(),color.saturation()-200,color.value());
	slupek.setColorAt(0.0,color);
	zbiornik.setColorAt(0.0,color);

        // Wyznaczenie wysoko¶ci s³upka;
	double factor =  m_value - m_min;
	       factor /= m_max - m_min;
	int temp = static_cast<int> (224.0 *  factor), height = temp + OFFSET;
	if (231 < temp  ) height = 231 + OFFSET; // by rtêæ dosz³a do koñca terometra ale go nie rozwali³a
	if (OFFSET-5 >= height )  height = OFFSET-5; // by nie zeszlo poni¿ej pieciu "pixeli" poni¿ej zera
	// Narysowanie s³upka  wraz z zbiorniczkiem rtêci
        painter.setPen(Qt::NoPen);
	painter.setBrush(slupek);
        painter.drawRect(-5,252+OFFSET - height ,10, height);
	painter.setBrush(zbiornik);
	painter.drawEllipse(QRectF(-10.0,257.5,20.0,20.0));
	painter.end(); // bardzo istotne - inaczej pod Xami jest b³±d
	// nie wiem czy to to powoduje krash pod win98 i brak bañki pod XP.
	// Na³o¿enie szklanej bañki
	drawBackground();

}// paintEvent
#undef OFFSET
