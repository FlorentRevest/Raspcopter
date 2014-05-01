QT       += core gui network svg
LIBS += -lqtermwidget -lpthread -lenet

POST_TARGETDEPS += 3rd-party/AnalogWidgets/analogwidgets/libanalogwidgets.a
LIBS += 3rd-party/AnalogWidgets/analogwidgets/libanalogwidgets.a

INCLUDEPATH += 3rd-party/AnalogWidgets/analogwidgets/analogwidgets \
               3rd-party/AnalogWidgets/analogwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ground-control-station
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    Network.cpp \
    Joystick.cpp \
    AttitudeWidget.cpp \
    3rd-party/qcustomplot/qcustomplot.cpp

HEADERS  += MainWindow.h \
    Network.h \
    Joystick.h \
    AttitudeWidget.h \
    3rd-party/qcustomplot/qcustomplot.h

FORMS    += mainwindow.ui

RESOURCES += \
    qressource.qrc
