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

#ifndef CHANNELDATA_H
#define CHANNELDATA_H
#include <utility>

namespace chart
{
  class ChannelData
  {
    public:
    /**
    * Init data channel in such a way that calling next will return first element of data
    * @return true if contain data 
    */
    virtual bool init() = 0 ; // ustawia pojemnik na pierwszym elemencie ...
    
    /**
    * Read x,y data from channel 
    * @return true if modre data can be fetched false if no more data is avaible 
    */
    virtual bool next(double & x, double & y) = 0;
    
    
    virtual bool maxX(double &) = 0;  
    virtual bool minX(double &) = 0; 
    
    virtual bool maxY(double &) = 0; 
    virtual bool minY(double &) = 0; 
    
        
    /** Number of elements/point in data channel */
    virtual int size() = 0;
    /** Virtual destructor */
    virtual ~ChannelData()
    { ; }
    
    
    virtual std::pair<double,double> findX(double x)=0; 

  };// class ChannelData
}; // namespace chart
#endif // CHANNELDATA_H
