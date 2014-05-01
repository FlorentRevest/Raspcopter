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

#ifndef CHART_H
#define CHART_H

#include <vector>
#include <memory> // auto_ptr
#include <QTimer>
#include <QPen> 
#include <QMenu> 

#include "widgetwithbackground.h"

#include "chart/channel.h"
#include "chart/scalegrid.h"
#include "chart/chartdecorator.h"


using namespace std;
using namespace chart;

typedef  vector<chart::Channel> Channels;

class Chart :  public WidgetWithBackground
{
  Q_OBJECT
  Q_PROPERTY (int channel     	 	READ channel      WRITE setChannel   )
  Q_PROPERTY (int position  		READ position     WRITE setPosition  )
  Q_PROPERTY (double size     		READ size         WRITE setSize      )
  Q_PROPERTY (double zoom			READ zoom         WRITE setZoom      ) 
  
  Q_PROPERTY ( int xMesh        READ xMesh        WRITE setXMesh         )
  Q_PROPERTY ( int yMesh        READ yMesh        WRITE setYMesh         )
  Q_PROPERTY ( int xSubMesh     READ xSubMesh     WRITE setXSubMesh      )
  Q_PROPERTY ( int ySubMesh     READ ySubMesh     WRITE setYSubMesh      )
  
  
  
  Q_PROPERTY (double channelMinimum    READ channelMinimum   WRITE setChannelMinimum    )
  Q_PROPERTY (double channelMaximum    READ channelMaximum   WRITE setChannelMaximum    )
  Q_PROPERTY (bool   channelShowScale  READ channelShowScale WRITE setChannelShowScale  )
  Q_PROPERTY (bool   channelVisible    READ channelVisible   WRITE setChannelVisible    )
  Q_PROPERTY (QColor channelColor	   READ channelColor     WRITE setChannelColor      )   
  Q_PROPERTY (QString channelName      READ channelName      WRITE setChannelName	    )
  // Q_PROPERTY (QFont  scaleFont              READ scaleFont  WRITE setScaleFont  )
  Q_PROPERTY (bool   showGrid	        READ showGrid   WRITE setShowGrid   )
  Q_PROPERTY (bool   showScale   		READ showScale  WRITE setShowScale  )
  Q_PROPERTY (bool   showLegend   		READ showLegend WRITE setShowLegend )
  Q_PROPERTY (bool   antialiasing           READ antialiasing WRITE setAntialiasing ) 
  
  
  Q_PROPERTY (QFont font                READ font         WRITE setFont          )
  public:
    Chart(QWidget *parent = 0);
    ~Chart();
    
    ScaleGrid & scaleGrid() { return m_scalegrid; } 
    Channels & channels() { return m_channels; } 
    
    /** Add channel with data */
    void addChannel(Channel & channel);

    /** Delete all object from Channels */
    void deleteChannelsData();
    
    void paintOn(QPainter & painter); 
    
  protected:
    /** Paint background */
    void paintBackground(QPainter & painter);// inherited form QMyWidgetWithBackground
    
    /** Paint cursor on data */
    void paintCursorPosition(QPainter & painter);   	 	
    
    //////////// E V E N T S /////////////
    void paintEvent(QPaintEvent *event); 	 // inherited from QMyWidgetWithBackgroun
    void contextMenuEvent ( QContextMenuEvent * e );
    void mouseMoveEvent ( QMouseEvent * e );
    
    //////////////// H E L P E R S ////////////////
    
    /** This method build decorators chain if you like you may substitute it and 
    * write your on decorators and init them here 
    */
    virtual void InitDecorators();
    /** Init coordinates of drawing area*/
    void initCoordinateSystem(QPainter & painter);
    
    
    
    
  public:
    
    int position()          const; 	
    double size()           const;	
    double channelMinimum() const;   
    double channelMaximum() const;   
    QColor channelColor()   const; 
    QString channelName()   const; 
    
    
    double zoom()		const; 
    
    int channel()  const;   
    int yMesh()    const;
    int xMesh()    const;
    int ySubMesh() const;
    int xSubMesh() const;
    
    bool showGrid()         const;
    bool isPaintOver()      const;
    bool channelShowScale() const;
    bool channelVisible()   const; 
    bool showScale()        const;
    bool showLegend()       const;
    bool antialiasing()   const; 
    
    QColor topBackgroundColor() const; 
    QColor bottomBackgroundColor() const; 
    QColor gridColor() const; 
    
    
    /** Build context menu */ 
    QMenu * contextMenu(); 
    
  public slots:
    
    void setPosition      (double i);
    void setPosition      (int i); 
    void setSize          (double i);
    void setSize 	      (int i); 
    
    void setChannelMinimum(double i); 
    void setChannelMaximum(double i); 
    void setChannelColor  (QColor i);
    void setChannelName   (QString i); 
    
    
    void setChannel ( int i);
    void setYMesh   ( int i); 
    void setXMesh   ( int i); 
    void setYSubMesh( int i); 
    void setXSubMesh( int i); 
    
    void setChannelShowScale(bool i); 
    void setChannelVisible  (bool i); 
    
    void setShowScale       (bool i); 
    void setShowGrid        (bool i); 
    void setShowLegend      (bool i);
    void setAntialiasing    (bool i); 
    
    void setFont       (QFont i);	 
    
    
    void setTopBackgroundColor(const QColor &c);
    void setBottomBackgrounColor(const QColor &c);
    void setGridColor(const QColor & c);
    void setZoom(double factor);
    
  signals: 
    void sizeChanged(int i); 
    void sizeChanged(double i); 
    void positionChanged(int i); 
    void positionChanged(double i); 
    
    void curPosChanged(const QPolygonF &); 
    
    void curRangeChanged(const QPolygonF &,const QPolygonF &);         
    
  protected slots:
    
    /** Set end of painting and repaint with antialiasing */
    void setPaintOver();
    
    void contextMenuActionTriggered(QAction * a);
    
  protected:
    
    /** ScaleGrid structure */
    ScaleGrid m_scalegrid;
    
    /** First decorator for chart painting */
    auto_ptr<ChartDecorator> m_painterDecorator;
    
    /** Vector of channels */
    Channels m_channels;
    unsigned int m_channel;
    /** Antialiasig timer */ 
    QTimer * timer;
    
    bool m_showLegend;
    bool m_antialiasing; 
    
    double m_zoom;
    
    /** Wielko¶æ osi X - to warto¶æ nie zmienna */
    double m_xsize;
    bool m_isPaintOver;
    
    ///// HELPER data ///// 
    /** Last cursor position */
    QPoint m_lastCurPoint,m_currentCurPoint; // mouseMoveEvent 
    /** Last cursor position in channels data */
    QPolygonF m_currentCurPositions,m_lastCurPositions; // mouseMoveEvent 
    /** Window with channels */
    QRect m_clip; // mouseMoveEvent 
    
    QColor m_topBackgroundColor; 
    QColor m_bottomBackgroundColor; 
    QColor m_gridColor;
    
};// class Chart 


#endif // CHART_H
