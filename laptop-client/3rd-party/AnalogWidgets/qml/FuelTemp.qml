  import QtQuick 1.0 

  Item 
  {
    width: 200
    height: width; 
    scale: width / 450 
    //clip : true 
      id: ft 
      property real temp : 120
      property real fuel: 50 
      function limit( l ) 
      {
	if (l>100) l = 100; 
	if (l < 0) l = 0 
	  return l; 
      }
    
    smooth: true 
    Item 
    {
      anchors.centerIn: parent   
      
      smooth: true 
      width:450
      height: width
  
    Image 
    {
      anchors.fill: parent 
      source: "svg/fueltemp_base.svg"; 
      smooth: true 
    } 

    Image 
    {
      x: 207 - width/2 
      y: 253.5 - height/2 
      id: temp_needle 
      source: "svg/fueltemp_needle.svg";
      rotation: 0 - 120/100 * ft.limit(ft.temp)  
      smooth: true 
      NumberAnimation on rotation { duration: 250 }
    }

    Image 
    {
      x: 243 - width/2 
      y: 190.5 - height/2 
      id: fuel_needle
      source: "svg/fueltemp_needle.svg";
      rotation: 60 + 120/100 * ft.limit(ft.fuel)  
      smooth: true 
      NumberAnimation on rotation { duration: 250 }
    }

    Image 
    {
      anchors.fill: parent 
      source: "svg/fueltemp_glass.svg"; 
      smooth: true 
    }

    }
  }