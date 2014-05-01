# Plik utworzony przez menad?era projektów kdevelopa
# ------------------------------------------- 
# Podkatalog wzgl?dem g?ównego katalogu projektu: ./test
# Cel to program:  

include (../Flags.pri)  

symbian{
POST_TARGETDEPS += ../analogwidgets/libanalogwidgets.a 
LIBS += ../analogwidgets/libanalogwidgets.a  
}


unix{
POST_TARGETDEPS += ../analogwidgets/libanalogwidgets.a 
LIBS += ../analogwidgets/libanalogwidgets.a  
}

win32-g++:{
POST_TARGETDEPS += ../analogwidgets/libanalogwidgets.a 
LIBS += ../analogwidgets/libanalogwidgets.a  
}


win32-msvc*:{
 POST_TARGETDEPS += ../analogwidgets/analogwidgets.lib
 LIBS += ../analogwidgets/analogwidgets.lib
}

wince*:{
 POST_TARGETDEPS += ../analogwidgets/analogwidgets.lib
 LIBS += ../analogwidgets/analogwidgets.lib
}



INCLUDEPATH += ../analogwidgets/analogwidgets \
               ../analogwidgets 
MOC_DIR = objects 
UI_DIR = . 
OBJECTS_DIR = ../objects 

CONFIG += release \
          warn_on 
TEMPLATE = app
TARGET = test

RESOURCES += test.qrc 
FORMS += testform.ui
DESTDIR=../test 
HEADERS += test.h \
           widgettester.h 

SOURCES += main.cpp \
           test.cpp \
           widgettester.cpp 

