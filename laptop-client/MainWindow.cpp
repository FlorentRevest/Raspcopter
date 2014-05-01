#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Joystick *joystick, Network* network) : QMainWindow(), ui(new Ui::MainWindow), m_joystick(joystick), m_network(network)
{
    ui->setupUi(this);

    connect(network, SIGNAL(connected()), this, SLOT(networkConnected()));
    connect(network, SIGNAL(disconnected()), this, SLOT(networkDisconnected()));

    connect(network, SIGNAL(setMeasuredValues(float,float,float)), this, SLOT(setMeasuredValues(float,float,float)));
    connect(network, SIGNAL(setCPUUsage(char)), this, SLOT(setCPUUsage(char)));
    connect(network, SIGNAL(setMemoryUsage(char)), this, SLOT(setMemoryUsage(char)));

    // Corner widgets
    QWidget *cornerWidget = new QWidget();
    QHBoxLayout *cornerLayout = new QHBoxLayout();
    m_ipLabel = new QLabel();
    m_ipLabel->setText(m_network->ip());
    m_led = new Led();
    m_led->setMinimumWidth(20);
    cornerLayout->addWidget(m_led);
    cornerLayout->addWidget(m_ipLabel);
    cornerLayout->setMargin(0);
    cornerWidget->setLayout(cornerLayout);
    ui->tabWidget->setCornerWidget(cornerWidget);

    // Instruments tab
    m_plot = ui->plot;
    m_plot->setInteractions(QCP::iRangeZoom);
    m_plot->legend->setVisible(true);

    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::blue));
    m_plot->graph(0)->setName("Roll");

    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::red));
    m_plot->graph(1)->setName("Pitch");

    m_plot->addGraph();
    m_plot->graph(2)->setPen(QPen(Qt::green));
    m_plot->graph(2)->setName("Yaw");

    m_plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    m_plot->xAxis->setDateTimeFormat("hh:mm:ss");
    m_plot->xAxis->setAutoTickStep(false);
    m_plot->xAxis->setTickStep(2);
    m_plot->axisRect()->setupFullAxesBox();

    connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_plot->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->save_plot_button, SIGNAL(clicked()), this, SLOT(savePlot()));

    // PID tab
    connect(ui->apply_pid_button, SIGNAL(clicked()), this, SLOT(applyPID()));

    // SSH tab
    ui->termWidget->setColorScheme("GreenOnBlack");
    ui->termWidget->sendText(QString("/usr/bin/ssh ").append(network->ip()).append("\n"));

    // Start the joystick reading loop
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateJoystick()));
    m_timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_joystick;
    delete m_network;
}

void MainWindow::setMeasuredValues(float roll, float pitch, float yaw)
{
    ui->attitude_widget->setRoll(roll);
    ui->roll_measured->setValue(roll);

    ui->attitude_widget->setPitch(pitch);
    ui->pitch_measued->setValue(pitch);

    ui->yaw_measured->setValue(yaw);

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.02) {
        m_plot->graph(0)->addData(key, roll);
        m_plot->graph(1)->addData(key, pitch);
        m_plot->graph(2)->addData(key, yaw);

        m_plot->graph(0)->rescaleValueAxis();
        m_plot->graph(1)->rescaleValueAxis();
        m_plot->graph(2)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    m_plot->xAxis->setRange(key+0.25, 12, Qt::AlignRight);
    m_plot->replot();
}

void MainWindow::setCPUUsage(char usage)
{
    ui->cpu_label->setText(QString::number(usage).append(" %"));
}

void MainWindow::setMemoryUsage(char usage)
{
    ui->cpu_label->setText(QString::number(usage).append(" %"));
}

void MainWindow::networkDisconnected()
{
    m_led->setColor(QColor(255, 0, 0));
}

void MainWindow::networkConnected()
{
    m_led->setColor(QColor(0, 255, 0));
}

void MainWindow::applyPID()
{
    float pidValues[9] = {(float)ui->roll_p_edit->value(), (float)ui->roll_i_edit->value(), (float)ui->roll_d_edit->value(),
                          (float)ui->pitch_p_edit->value(), (float)ui->pitch_i_edit->value(), (float)ui->pitch_d_edit->value(),
                          (float)ui->yaw_p_edit->value(), (float)ui->yaw_i_edit->value(), (float)ui->yaw_d_edit->value()
                         };
    m_network->send(SET_PID_VALUES, pidValues, sizeof(float) * 9, true);
}

void MainWindow::savePlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Plot as .csv", QDir::homePath() + "/Plot-" + QDateTime::currentDateTime().toString().replace(" ", "-") + ".csv", "Data Tables (*.csv)");

    QFile file(fileName);
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream output(&file);
        output << "Roll,Pitch,Yaw\n";

        QList<QCPData> rollValues = m_plot->graph(0)->data()->values();
        QList<QCPData> pitchValues = m_plot->graph(1)->data()->values();
        QList<QCPData> yawValues = m_plot->graph(2)->data()->values();
        for(int i = 0 ; i < rollValues.count() ; i++)
            output << rollValues.at(i).value << "," << pitchValues.at(i).value << "," << yawValues.at(i).value << "\n";

        file.close();
    }
}

void MainWindow::updateJoystick()
{
    JoystickEvent event;
    if (m_joystick->sample(&event)) {
        if (event.isAxis()) {
            float data = 0;
            switch(event.number) {
            case 0:
                ui->roll_joystick->setValue(event.value*100/32767);
                data = (float)(event.value*100/32767);
                m_network->send(SET_WANTED_ROLL, &data, sizeof(float), false);
                ui->attitude_widget->setWantedRoll(data);
                ui->attitude_widget->repaint();
                break;
            case 1:
                ui->pitch_joystick->setValue(event.value*100/32767);
                data = (float)(event.value*100/32767);
                m_network->send(SET_WANTED_PITCH, &data, sizeof(float), false);
                ui->attitude_widget->setWantedPitch(data);
                ui->attitude_widget->repaint();
                break;
            case 3:
                ui->throttle_joystick->setValue((event.value+32767)*50/32767);
                data = (float)((event.value+32767)*50/32767);
                m_network->send(SET_WANTED_THROTTLE, &data, sizeof(float), false);
                break;
            case 4:
                ui->yaw_joystick->setValue(event.value*100/32767);
                data = (float)(event.value*100/32767);
                m_network->send(SET_WANTED_YAW, &data, sizeof(float), false);
                break;
            }
        }
    }
}
