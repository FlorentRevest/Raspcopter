/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2014 - Florent Revest <florent.revest666@gmail.com>

 * Raspcopter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Raspcopter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Raspcopter.  If not, see <http://www.gnu.org/licenses/>.
 * ================================================================== */

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
    QPushButton *m_startServer, *m_stopServer, *m_reconnect;

public slots:
    void updateJoystick();

    void applyPID();
    void savePlot();

    void setMeasuredValues(float roll, float pitch, float yaw);
    void setCPUUsage(char usage);
    void setMemoryUsage(char usage);

    void networkDisconnected();
    void networkConnected();

    void startServer();
    void stopServer();
    void reconnect();
};

#endif // MAINWINDOW_H
