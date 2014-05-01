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
  			channel.h - Copyright coder
**************************************************************************/

#ifndef CHANNEL_H
#define CHANNEL_H
#include <QString>
#include <QPen>
#include "channeldata.h"


//class Iterator;
namespace chart {
/** Stuktura zawieraj±ca dane na temat konkretnego kana³u */
class Channel  {

public:

   enum { Line = 0x1, Dots = 0x2 };
  
  /** Default constructor */
  Channel();

  /**
  * Parametrized construcotr 
  * Pozwala na okre¶lenie warto¶ci minimalnych oraz maksymalnych
  * @param min - scale minimum
  * @param max - scale maximum 
  * @param name - Name of channel @see setName
  * @param pen  - pen type 
  */
  Channel(double min,double max, ChannelData * data,QString name,QPen pen );
  
  ~Channel(); 
  
   void setPen(const QPen & pen);
   QPen pen() const; 
   
   void setName(const QString & name);
   QString name() const; 
  
   /** Zwraca wska¼nik do "pojemnika" z danymi */ 
   ChannelData * data() const; 
   
   /** Maximal scale value that have to be on chart */
   double maximum() const;
   /** set Maximal scale value that have to be on chart */
   void setMaximum(double i);
   /** Minimal scale value that have to be on chart */
   double minimum() const ;
   /** Set minimal scale value that have to beon chart */
   void setMinimum(double i);

   /** set (normaly calculated from minimum and maximum ) min and max values on scale */
   void setCalcMinMax(double a,double b);
   /** Gets values min and maximum values on scale */
   void getCalcMinMax(double &a, double &b);

   /** Is scale visible */
   bool showScale() const;
   /** Set scale visible */
   void setShowScale(bool i );

   /** Is chanel visible */
   bool visible() const;

   /** Set channel visible  @see visible */
   void setVisible(bool i); 

   /** Is channel legend visible */
   bool showLegend() const; 

   /** set channel Legend visible */
   void setShowLegend(bool i);

   /** Type of Channel Channel::Line lub Channel::Dots  used by decorators @see ChannelDecorator */ 
   unsigned int type(); 

   /** Set type of Channel Channel::Line or Channel::Dots 
    * allowed are also any arbitary types as long as custom ChannelDecorator recognize them 
    */

   void setType(unsigned int); 
   protected: 
  
     
   QPen m_pen;
  
   QString m_name;
  
  ChannelData * m_data;
  
  
  unsigned int m_type; 

  
   double m_min;
  
   double m_max;
  
   double m_calc_min;
  
   double m_calc_max;

  
   bool m_showScale;
   bool m_visible; 
   bool m_showLegend; 

  public: 


}; //  class channel
} // namespace chart
#endif //CHANNEL_H
