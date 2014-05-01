#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPen>

class AttitudeWidget : public QWidget
{
    Q_OBJECT
public:
    AttitudeWidget(QWidget *parent = 0);
    void setRoll(int roll);
    void setPitch(int pitch);
    void setWantedRoll(int roll);
    void setWantedPitch(int pitch);

protected:
    void paintEvent(QPaintEvent *);

private:
    int m_roll, m_pitch, m_wantedRoll, m_wantedPitch;
};

#endif // MAINVIEW_H
