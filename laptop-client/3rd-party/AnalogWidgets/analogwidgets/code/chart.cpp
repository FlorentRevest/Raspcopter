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
#include <cstdio> 
#include <cstring> 



#include "chart.h"
#include "chart/standard/scalegriddecorator.h"
#include "chart/standard/glassdecorator.h"
#include "chart/standard/channeldecorator.h"
#include "chart/standard/legenddecorator.h"

/* 

  @TODO Zanim to zrobisz - przemy¶l gruntownie mechanizm kana³ów ... 
   
2. Zmieniæ nieco interfejs chartów ... stworzyæ tzw. grupy kana³ów ... 
       oraz dodaæ mo¿liwo¶æ wy¶wietlania wybranych kana³ow z wykresu 1 na wykresie 2. 
       Przy okazji mo¿na by by³o podmieniæ w³a¶ciwo¶ci tych kana³ów ... np kolor itp. 
       Ka¿dy kana³ identyfikowany by³ by odatkowo przez swoj± nazwê ... 
       Dodaæ kontekstowe menu z standardowymi opcjami dla Chart'a oraz list± grup kana³ów 
       co pozwoli³o by zarz±dzaæ grup± kana³ów oraz ka¿dym kana³em w grupie osobno. 
       
       Pomys³ na implementacjê: 
       Je¿eli kana³ nie ma nazwy nie jest wy¶wietlany w Legendzie ... 
       Interfejs kana³ów pozostaje taki sam ... dochodz± tylko nowe metody ktore mog± zwróciæ 
       kana³y w nowej grupie oraz pozwala to na tworzenie nowych kana³ów w nowych grupach :) 
       
       np . addChannel("Nazwa grupy kana³ów", Channel(...)); 
       oraz addChannel(nr_grupy,Channel(...)); 
            addChannel(Channel(...)); // dodaje channel do podstawowej grupy 
            
            channels(); zwraca referencjê do kana³ów we wszystkich grupach
            channels(nr_grupy) ... zwraca referencjê do kana³ow konkretnej grupy :D 
            channels("Nazwa grupy") ... 
                        
           pokazanie grupy kana³ów z chart'a 1 na charcie 2. to 
             
           chart1->addGroup("new group",chart2->channles("Wskazana grupa"); 
           potem mo¿na ju¿ rêcznie sobie dokonfigurowaæ resztê ... np. 
           chart1->channels("Wskazana grupa")[1].isVisible(false); 
           lub chart1->channels("Wskazana grupa").remove("Pozycja tloka"); 
           
           
             
    Pomys³ 2 zdecydowanie bardziej mi siê podoba ... jest bardziej uniwersalny 
    mo¿na by go zastosowaæ te¿ w innych aplikacjach ... 
    
    Na razie zrobiæ na sztywno ... dodawane kana³y po prostu jak do tej pory. 
    
 */   


using namespace std; 

//
//      public
//
Chart::Chart(QWidget *parent)
	: WidgetWithBackground(parent)
{
   setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
   setWindowTitle(tr("Chart diagram"));
   m_channel=0;
   timer = new QTimer(this);
   timer->setInterval(1000);
   m_isPaintOver = false;
   connect(timer,SIGNAL(timeout()),this,SLOT(setPaintOver()));
   InitDecorators();
  // setChannel(1); 
   m_showLegend = true;
   m_zoom = 1.0; 
   m_xsize = m_scalegrid.size=1000.0; 
   m_antialiasing = true; 
   
   m_topBackgroundColor = QColor(0,0,150); 
   m_bottomBackgroundColor = Qt::black; 
   m_gridColor = QColor(40,40,180);

}

Chart::~Chart()
{
  if (timer) delete timer;
  timer = NULL;
}

void Chart::addChannel(Channel & channel)
{
  m_channels.push_back(channel);
  updateWithBackground();
}


void Chart::deleteChannelsData()
{
    for (unsigned int i = 0 ; i < m_channels.size() ; i++)
        delete m_channels[i].data();
}


void Chart::paintOn(QPainter & painter)
{
  if (m_painterDecorator.get()) 
  {
     m_modified = true; 
     m_isPaintOver = true; 
     m_painterDecorator->paint(painter,this); 
     m_modified = false; 
     m_painterDecorator->paint(painter,this); 
  }
}


//
//      private
//

void Chart::InitDecorators()
{
       m_painterDecorator.reset
	(
           new Standard::ScalesGridDecorator
          (
            new Standard::ChannelDecorator
		( new Standard::LegendDecorator(NULL) ) // new Standard::GlassDecorator(NULL)
          )
        );
}

void Chart::setPaintOver()
	{
          m_isPaintOver = true;
          timer->stop();
          update();
          // By malowalo normalnie wygladzone no chyba ze malujemy z duza czestoliwoscia ...
          m_isPaintOver = true; // kiedy ma byc malowane w antialiasingu jak czesto sie da ...

	}
void Chart::paintEvent(QPaintEvent * /*event */)
{
   drawBackground();
   QPainter painter(this);
   //initCoordinateSystem(painter);
 
   if (m_painterDecorator.get()) m_painterDecorator->paint(painter,this); 
   
   if (!m_isPaintOver) timer->start();
   m_isPaintOver = false;
   paintCursorPosition(painter); 
}

void Chart::paintBackground(QPainter & painter)
{

   //initCoordinateSystem(painter);
   if (m_painterDecorator.get()) m_painterDecorator->paint(painter,this);
}

void Chart::initCoordinateSystem(QPainter & /*painter*/)
{
   	;

}

//***************************
//	Public Properties 
//***************************

// position 
int Chart::position()          const 	
{ 
  return static_cast<int>( m_scalegrid.pos );   
}

void Chart::setPosition(double i)
{
	m_scalegrid.pos=i; 
        update();
        positionChanged( i ); 
        positionChanged(static_cast<int> (i));  
}

void Chart::setPosition(int i)
{
   setPosition(static_cast<double>(i)); 
}

// size 
double Chart::size()           const	
{
  return m_xsize; 
}

void Chart::setSize(double i)
{
      	if (i>0.00001)
      	{
      	 m_xsize = i; 
      	 m_scalegrid.size=m_xsize*m_zoom;
	 update();
	}
	sizeChanged( i ); 
	sizeChanged( static_cast<int> (i)); 
}

void Chart::setSize(int i)
{
  setSize(static_cast<double>(i)); 
}

// ***** channelMinimum 
double Chart::channelMinimum() const   
{ 
  if (m_channels.size())
   return m_channels[m_channel].minimum();
  return 0.0; 
}

void Chart::setChannelMinimum(double i) 
{ 
  if (m_channels.size())
  {
    m_channels[m_channel].setMinimum(i);
    updateWithBackground(); 
  }
}

// ****** channelMaximum 
double Chart::channelMaximum() const   
{ 
  if (m_channels.size())
   return m_channels[m_channel].maximum();
  
  return 0.0; 
}
      	
void Chart::setChannelMaximum(double i) 
{
  if (m_channels.size())
  {
    m_channels[m_channel].setMaximum(i);  
    updateWithBackground(); 
  }
}

// ***** channel 
int Chart::channel()  const   
{ 
  return m_channel; 
}

void Chart::setChannel( int i)
{
	m_channel = i;
        if (m_channel >= m_channels.size())
        {
          m_channels.push_back(Channel());
          updateWithBackground();
        }
}

 

// channelColor
QColor Chart::channelColor()      const
{
  QColor C(255,255,255); 
  if (m_channels.size())
  C = m_channels[m_channel].pen().color();
 
  return C;
}

void Chart::setChannelColor( QColor i )
{
  if (m_channels.size())
   {
     m_channels[m_channel].pen().setColor(i);
     updateWithBackground(); 
   }
   
}

// ****** yMesh 
int Chart::yMesh()    const   { return m_scalegrid.m_yMesh;}

void Chart::setYMesh   ( int i) 
{  
  if (i>0)
  {
    m_scalegrid.m_yMesh = i;
    updateWithBackground(); 
  }
}

// ****** x Mesh 
int Chart::xMesh()    const   { return m_scalegrid.m_xMesh;}

void Chart::setXMesh   ( int i) 
{ 
  if (i>0)
  {
    m_scalegrid.m_xMesh = i; 
    updateWithBackground(); 
  }
}

// ****** ySubMesh 
 int Chart::ySubMesh() const   { return m_scalegrid.m_ySubMesh;}

void Chart::setYSubMesh( int i) 
{
   if (i>=0)
   {
     m_scalegrid.m_ySubMesh = i;
     updateWithBackground(); 
   }
}
// ****** xSubMesh 
int Chart::xSubMesh() const   { return m_scalegrid.m_xSubMesh;}

void Chart::setXSubMesh( int i) 
{ 
  if (i>=0)
  {
    m_scalegrid.m_xSubMesh = i; 
    updateWithBackground(); 
  }
}

// ***** channelShowScale 
bool Chart::channelShowScale() const	
{ 
 if (m_channels.size())
  return m_channels[m_channel].showScale(); 
  return false; 
}

bool Chart::channelVisible() const
{
  if (m_channels.size())
    return m_channels[m_channel].visible(); 
  return false; 
}

void Chart::setChannelShowScale(bool i) 
{
   if (m_channels.size())
   { 
     m_channels[m_channel].setShowScale(i);
     updateWithBackground(); 
   }
}

void Chart::setChannelVisible(bool i) 
{
  if (m_channels.size())
  { 
    m_channels[m_channel].setVisible(i);
    updateWithBackground(); 
  }
}


// ***** channelName 
QString Chart::channelName () const
{
  QString name; 
  if (m_channels.size())
    name = m_channels[m_channel].name() ; 
  return name ;
}

void Chart::setChannelName (QString i) 
{
  if (m_channels.size())
  {
    m_channels[m_channel].setName(i); 
    update(); 
  }
}
// ***** showScale 
bool Chart::showScale()        const	{ return m_scalegrid.showScale;}

void Chart::setShowScale(bool i) 
{
   m_scalegrid.showScale = i; 
   updateWithBackground(); 
}

// ****** showLegend 
bool Chart::showLegend()       const    { return m_showLegend; } 

void Chart::setShowLegend(bool i)
{
  m_showLegend = i;
  updateWithBackground(); 
}

bool Chart::antialiasing() const {  return m_antialiasing; }

QColor Chart::topBackgroundColor() const
{
  return m_topBackgroundColor;  
}


QColor Chart::bottomBackgroundColor() const
{
  return m_bottomBackgroundColor;  
}

QColor Chart::gridColor() const
{
  return m_gridColor;  
}



void Chart::setAntialiasing(bool i)
{
  m_antialiasing = i; 
  updateWithBackground();    
}


// ****** showGrid 
bool Chart::showGrid()         const	{ return m_scalegrid.showGrid; }

void Chart::setShowGrid(bool i) 
{ 
  m_scalegrid.showGrid = i;
  updateWithBackground();  
}

// ***** zoom 
double Chart::zoom()	       const
{
  return m_zoom; 
}

void Chart::setZoom(double factor)
{
  if (fabs(factor)>0.01)
  {
    m_zoom = factor;
    m_scalegrid.size = m_xsize*m_zoom; 
    update();
  }
}

// Zas³ania setFont QWidget by mo¿na by³o od¶wie¿yæ ca³y komponent 
void Chart::setFont(QFont i) 
{ 
   QWidget::setFont(i);
   updateWithBackground(); 
}

void Chart::setTopBackgroundColor( const QColor & c) 
{
  m_topBackgroundColor = c; 
  updateWithBackground();  
}

void Chart::setBottomBackgrounColor( const QColor & c) 
{
  m_bottomBackgroundColor = c; 
  updateWithBackground();  
}

void Chart::setGridColor( const QColor & c) 
{
  m_gridColor=c; 
  updateWithBackground(); 
}


// Ustawia koniec malowania i nastêpuje malownie z antialiasingiem 
bool Chart::isPaintOver()      const    { return m_isPaintOver; }


void Chart::contextMenuEvent ( QContextMenuEvent * e )
{
  contextMenu()->exec(e->globalPos()); 
}

/** Buduje zwyk³e menu */ 
QMenu * Chart::contextMenu()
{
  QMenu * menu = new QMenu(this); 
  // By specyifczne akcje odpala³y sie tutaj 
  connect(menu,SIGNAL(triggered(QAction *)),this,SLOT(contextMenuActionTriggered(QAction *)));
    
  QAction * a_data,*a_scale,*a; 
     
  a_data  = menu->addAction(trUtf8("Dane")); 
  a_scale = menu->addAction(trUtf8("Skala pionowa"));

       QMenu * data = new QMenu(this); 
       QMenu * scale = new QMenu(this); 
       a_data->setMenu(data);        
       a_scale->setMenu(scale);
       Channels::iterator i = m_channels.begin(); 
       unsigned int ch_no = 0; 
       while (i!=m_channels.end())
       {
          QString code = "c "; 
          code += QString::number(ch_no); 
          
          // Tutaj czy kana³ ma byæ pokazywany w ogóle 
          a = data->addAction(i->name()); 
          a->setCheckable(true);
          a->setChecked(i->visible()); 
          a->setObjectName(code+QString(" show")); 
          
          
          // Pokzaywanie skali 
          a = scale->addAction(i->name()); 
          a->setCheckable(true);
          a->setChecked(i->showScale()); 
          a->setObjectName(code+QString(" scale")); 
          
          
          i++;
          ch_no++; 
       }
     
     
     
  a = menu->addAction(""); 
  a->setSeparator(true);    
     
  a = menu->addAction(trUtf8("Siatka"));
  a->setCheckable(true); 
  a->setChecked(showGrid()); 
  connect(a,SIGNAL(toggled(bool)),this,SLOT(setShowGrid(bool)));  
  

  a = menu->addAction(trUtf8("Skala pozioma")); 
  a->setCheckable(true);
  a->setChecked(showScale()); 
  connect(a,SIGNAL(toggled(bool)),this,SLOT(setShowScale(bool))); 
    
  a = menu->addAction(trUtf8("Legenda")); 
  a->setCheckable(true); 
  a->setChecked(showLegend()); 
  connect(a,SIGNAL(toggled(bool)),this,SLOT(setShowLegend(bool))); 
    
  a = menu->addAction(trUtf8("Antialiasing"));
  a->setCheckable(true);
  a->setChecked(antialiasing());
  connect(a,SIGNAL(toggled(bool)),this,SLOT(setAntialiasing(bool))); 
  menu->addActions(actions());
  return menu; 
}

/** Wywo³anie menu kontekstowego */ 
void Chart::contextMenuActionTriggered(QAction * a)
{
  qDebug("Action triggered %s",a->objectName().toLocal8Bit().data()); 
  QString name = a->objectName(); 
  char command[10]; 
  int channel;  char c; 
  if ('c'==name[0])
  {
    sscanf(a->objectName().toLocal8Bit().data(),"%c %d %s",&c,&channel,command); 
    if (0==strcmp(command,"show"))
      m_channels[channel].setVisible(!m_channels[channel].visible()); 
    if (0==strcmp(command,"scale"))
      m_channels[channel].setShowScale(!m_channels[channel].showScale()); 
    updateWithBackground(); 
  }
}

/** Ruch mysz± */ 
void Chart::mouseMoveEvent ( QMouseEvent * e )
{
  if (!hasMouseTracking()) return; 
   
  m_clip = QRect (0,0,width(),height()); 
  m_currentCurPoint = e->pos(); 
  m_currentCurPositions.clear();
  
  if (m_painterDecorator.get()) 
     m_painterDecorator->absPosition(m_currentCurPoint,m_currentCurPositions,this,m_clip);
  
  m_currentCurPoint.rx()+=m_clip.x();
  m_currentCurPoint.ry()+=m_clip.y(); 
  
  if (m_clip.contains(m_currentCurPoint))
  {
  
     emit curPosChanged(m_currentCurPositions); 
    
    
     if (e->buttons()&&Qt::LeftButton)
     {
        // po prostu bêdzie ramka ... 
        emit curRangeChanged(m_currentCurPositions,m_lastCurPositions);
     }
     else 
     {
        m_lastCurPoint = m_currentCurPoint; 
        m_lastCurPositions = m_currentCurPositions;    
     }
   update(); 
  }
}

/** Maluje pozycjê kursora na obiekcie danych */  	 	
void Chart::paintCursorPosition(QPainter & painter)
{
  if (!m_clip.contains(m_currentCurPoint)) return; 
  
  painter.setPen(QColor(0,150,150)); 
  if (m_lastCurPoint==m_currentCurPoint) 	 	// tylko linia do namalowania 
  {

    painter.drawLine(
                       QPoint(m_currentCurPoint.x(),m_clip.y()),
                       QPoint(m_currentCurPoint.x(),m_clip.y()+m_clip.height())
                     );
    painter.drawLine( QPoint(m_clip.x(),m_currentCurPoint.y()),
                      QPoint(m_clip.x()+m_clip.width(),m_currentCurPoint.y())
                    );  	 	
   	 	
  }
  else 
  { 	 
  	
    QRect horiz(QPoint(m_clip.x(),m_currentCurPoint.y()),
               QPoint(m_clip.x()+m_clip.width()-3,m_lastCurPoint.y())
               ); 
               
    QRect vert(QPoint(m_currentCurPoint.x(),m_clip.y()),
               QPoint(m_lastCurPoint.x(),m_clip.y()+m_clip.height())
               );
                  
    painter.setBrush(QColor(0,150,150,100));//Qt::NoBrush); //
    QPen pen = painter.pen(); 
    pen.setWidthF(1.5); 
    painter.setPen(pen);
   // painter.drawRect(vert); 
    QRect intersect = vert.intersected(horiz); 
    painter.drawRect(intersect); 	 	
  }	 	
}// paintCursorPositon 


