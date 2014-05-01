# Plik utworzony przez mened?era projektów kdevelopa
# ------------------------------------------- 
# Podkatalog wzgl?dem g?ównego katalogu projektu: ./analogwidgets/code
# Cel to biblioteka analogwidgets
RESOURCES += analogwidgets.qrc 

HEADERS += ../analogwidgets/chart/chartdecorator.h \
           ../analogwidgets/chart/channeldata.h \
           ../analogwidgets/chart/channel.h \
           ../analogwidgets/chart/datacontainers.h \
           ../analogwidgets/chart/standard/labelsdecorator.h \
           ../analogwidgets/chart/standard/legenddecorator.h \
           ../analogwidgets/chart/standard/scalegriddecorator.h \
           ../analogwidgets/chart/standard/glassdecorator.h \
           ../analogwidgets/chart/standard/channeldecorator.h \
           ../analogwidgets/chart/scalegrid.h \
           ../analogwidgets/led.h \
           ../analogwidgets/functions.h \
           ../analogwidgets/manometer.h \
           ../analogwidgets/chart.h \
           ../analogwidgets/thermometer.h \
           defines.h \
           ../analogwidgets/abstractmeter.h \
           ../analogwidgets/wallclock.h \
           ../analogwidgets/widgetwithbackground.h \
           ../analogwidgets/bitmapbutton.h \
	   ../analogwidgets/counter.h \
	   ../analogwidgets/scriptwidget.h \
	   ../analogwidgets/potentiometer.h \
	   item.h 
	   
SOURCES += chart/scalegrid.cpp \
           chart/standard/labelsdecorator.cpp \
           chart/standard/glassdecorator.cpp \
           chart/standard/channeldecorator.cpp \
           chart/standard/legenddecorator.cpp \
           chart/standard/scalegriddecorator.cpp \
           chart/channel.cpp \
           chart.cpp \
           functions.cpp \
           led.cpp \
           manometer.cpp \
           thermometer.cpp \
           wallclock.cpp \
           chart/chartdecorator.cpp \
           abstractmeter.cpp \
           widgetwithbackground.cpp \
           bitmapbutton.cpp \
	   counter.cpp \
	   scriptwidget.cpp \
	   potentiometer.cpp 
	   
# Plik utworzony przez menad?era projektów kdevelopa



INCLUDEPATH += .. \ 
               ../analogwidgets 

	       
include (../../Flags.pri )
OBJECTS_DIR = ../objects
TARGET = analogwidgets
DESTDIR = ../
CONFIG += release \
warn_on \
staticlib
TEMPLATE = lib


headers.files += ../analogwidgets/*.h
headers_chart.files += ../analogwidgets/chart/*.h
headers_standard.files += ../analogwidgets/chart/standard/*.h 
headers.path += $$INSTALL_INCLUDEDIR/analogwidgets
headers_chart.path += $$INSTALL_INCLUDEDIR/analogwidgets/chart
headers_standard.path += $$INSTALL_INCLUDEDIR/analogwidgets/chart/standard 

staticlib.files += ../libanalogwidgets.a 
staticlib.path += $$INSTALL_LIBDIR/ 


INSTALLS += headers headers_chart headers_standard staticlib 


WIN32{
  DEFINES+= WIN32
}
