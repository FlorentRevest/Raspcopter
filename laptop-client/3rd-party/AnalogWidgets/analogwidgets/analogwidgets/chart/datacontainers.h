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

#ifndef DATACONTAINERS_H
#define DATACONTAINERS_H
#include <cmath> 
#include <algorithm>
#include "channeldata.h"

using namespace chart;
using namespace std;

/**
* Klasa szablonowa na pojemniki z dostêpem sekwencyjnym zawieraj±cych dane typu pair<double,double>
* jest pochodn± klasy ChannelData co czyni j± ideln± do zastosowania jako ¼ród³o danych
* dla komponentu typu Chart.
* @see ChannelData
*/


template <typename type>
class PairDataContainer : public ChannelData
{

  type & m_container;
  typename type::iterator m_iterator;
  public:

  PairDataContainer ( type & container ): m_container(container)
  { ; }

  bool init()
  {
    m_iterator = m_container.begin();
    return !m_container.empty();
  }

  bool next(double & x , double & y)
  {
    if (m_container.end() == m_iterator) 
      return false; 
    
     x = static_cast<double> (m_iterator->first);
     y = static_cast<double> (m_iterator->second);
        
    ++m_iterator; 
    
    return true;
  }
  
  std::pair<double,double> findX (double)
  {
   // @TODO Ta funkcja musi zostaæ napisana ...  return pair<double,double>(0,0); 
    return pair<double,double>(0,0); 
  }
  
  
  bool maxX(double & max)
  {
      init();
      double x,y;
      next(x,y);
      max=x;
      while (next(x,y))
      {
          if (x > max)
               max = x;
      }
     return true;
  }
  
  bool minX(double & min)
  {
      init();
      double x,y;
      next(x,y);
      min=x;
      while (next(x,y))
      {
          if (x < min)
               min = x;
      }
      return true;
  }
  
  bool maxY(double &max )
  {
      init();
      double x,y;
      next(x,y);
      max=y;
      while (next(x,y))
      {
          if (y > max)
               max = y;
      }
      return true;
  }
  
  bool minY(double & min)
  {
      init();
      double x,y;
      next(x,y);
      min=y;
      while (next(x,y))
      {
          if (y < min)
               min = y;
      }
      return true;
  }

  int size()
  {
     return m_container.size(); 
  }
}; // class DataContainers


#include <iostream> 
using namespace std; 
/**
* Klasa szablonowa na 2 pojemniki z dostêpem sekwencyjnym zawieraj±cych dane skalarne (double,int,etc.)
* jest klas± pochodn± klasy ChannelData co czyni j± idealn± do zastosowania jako ¼ród³o danych
* dla komponentu typu Chart
*/




template <typename T >
class between
{
 T val;
 public:
 between(T v):val(v)
 { ; } 
 bool operator()(T & a,T & b)
 {
  return (a<val && val<=b);
 }
};



template <typename type1, typename type2>
class DoubleDataContainer : public ChannelData
{
  type1 & m_xcontainer;
  type2 & m_ycontainer;
  typename type1::iterator m_xit;
  typename type2::iterator m_yit;
  
  typename type1::iterator m_xfind_it;
  typename type2::iterator m_yfind_it;
 
  
  public:
  DoubleDataContainer(type1 & xContainer, type2 & yContainer)
	  : m_xcontainer(xContainer),m_ycontainer(yContainer)
  { 
    init();
  }
  
  bool init()
  {
    m_xit = m_xcontainer.begin();
    m_yit = m_ycontainer.begin();
    return ! (m_xcontainer.empty() || m_ycontainer.empty() );
  }

  bool next( double & x, double & y)
  {
    if ( (m_xcontainer.end() == m_xit ) || (m_ycontainer.end() == m_yit) )
          return false; 
    x = static_cast<double> (*m_xit++);
    y = static_cast<double> (*m_yit++);

   return true;
  }

  int size()
  {
	return m_xcontainer.size(); 
  }

  bool maxX(double & x) 
  {
    typename type1::iterator i = max_element(m_xcontainer.begin(),m_xcontainer.end());
    if (i!=m_xcontainer.end()) 
    {
      x = *i; 
      return true;
    }
    return false;
  }

  bool minX(double & x) 
  {
    typename type1::iterator i = min_element(m_xcontainer.begin(),m_xcontainer.end());
    if (i!=m_xcontainer.end()) 
    { 
      x = *i; 
      return true; 
    }
    return false; 
  }

  bool maxY(double & y) 
  {

    typename type2::iterator i = max_element(m_ycontainer.begin(),m_ycontainer.end());
    if (i!=m_ycontainer.end())
    {
        y = *i;
        return true;
    }

    return false;
  }

  bool minY(double & y)
  {
    typename type2::iterator i = min_element(m_ycontainer.begin(),m_ycontainer.end());
    if (i!=m_ycontainer.end()) 
    { 
      y = *i; 
      return true; 
    }
    return false;
  }
  
  std::pair<double,double> findX (double x)
  {
    typedef typename type1::value_type just_type; 
    typename type1::iterator xi=adjacent_find(m_xcontainer.begin(),m_xcontainer.end(),between<just_type>(static_cast<just_type>(x))); 
    
    if (xi==m_xcontainer.end())
        return pair<double,double>(0.0,0.0); 
    
    typename type2::iterator yi = m_ycontainer.begin();   

    while (xi!=m_xcontainer.begin() && yi!=m_ycontainer.end())
    { xi--; yi++; }
    if (yi!=m_ycontainer.end())
     yi++;
    Q_ASSERT(yi!=m_ycontainer.end());
    return pair<double,double>(*xi,*yi); 
  }


}; // class DoubleDataContainer


#endif // DATACONTAINERS_H
