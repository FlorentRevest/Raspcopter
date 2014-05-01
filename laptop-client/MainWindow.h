#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include <qtermwidget.h>

#include "led.h"

#include "3rd-party/qcustomplot/qcustomplot.h"

#include <list>
#include <vector>

#include "Network.h"
#include "AttitudeWidget.h"
#include "Joystick.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Joystick *joystick, Network *network);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Joystick *m_joystick;
    Network *m_network;
    QTimer *m_timer;
    Led *m_led;
    QLabel *m_ipLabel;
    QCustomPlot *m_plot;

public slots:
    void updateJoystick();

    void applyPID();
    void savePlot();

    void setMeasuredValues(float roll, float pitch, float yaw);
    void setCPUUsage(char usage);
    void setMemoryUsage(char usage);

    void networkDisconnected();
    void networkConnected();
};

#endif // MAINWINDOW_H
