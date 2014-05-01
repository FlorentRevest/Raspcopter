# Plik utworzony przez mened?era projektów kdevelopa
# ------------------------------------------- 
# Podkatalog wzgl?dem g?ównego katalogu projektu: ./analogwidgets/plugins
# Cel to biblioteka analogwidgets_plugin


HEADERS += analogwidgets_plugin.h \
           chart_plugin.h \
           defines.h \
           led_plugin.h \
           manometer_plugin.h \
           thermometer_plugin.h \
           wallclock_plugin.h \
           bitmapbutton_plugin.h \
	   counter_plugin.h \
	   svgfile_taskmenu.h \
	   scriptwidget_plugin.h \
	   potentiometer_plugin.h 


SOURCES += analogwidgets_plugin.cpp \
           chart_plugin.cpp \
           led_plugin.cpp \
           manometer_plugin.cpp \
           thermometer_plugin.cpp \
           wallclock_plugin.cpp \
	   bitmapbutton_plugin.cpp \
	   counter_plugin.cpp \
	   svgfile_taskmenu.cpp \
	   scriptwidget_plugin.cpp \
	   potentiometer_plugin.cpp 


unix:{             
POST_TARGETDEPS += ../libanalogwidgets.a 
LIBS += ../libanalogwidgets.a  
}

win32-g++:{             
POST_TARGETDEPS += ../libanalogwidgets.a 
LIBS += ../libanalogwidgets.a  
}


win32-msvc*:{
 POST_TARGETDEPS += ../analogwidgets.lib
 LIBS += ../analogwidgets.lib
}

wince*:{
 POST_TARGETDEPS += ../analogwidgets.lib
 LIBS += ../analogwidgets.lib
}

QT += xml svg script 

INCLUDEPATH += ../analogwidgets \
..
	       
MOC_DIR =     ..\objects
OBJECTS_DIR = ..\objects
TARGET =       analogwidgets_plugin
DESTDIR =      ../
CONFIG += release \
          warn_on \
	  designer \ 
          plugin
TEMPLATE = lib

include (../../Flags.pri )

target.path += $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
