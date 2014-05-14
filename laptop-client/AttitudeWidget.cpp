#include "AttitudeWidget.h"

// This class should be replaced by a camera view (with Phonon?) one day or another.

AttitudeWidget::AttitudeWidget(QWidget *parent) : QWidget(parent)
{
    m_roll = m_pitch = 0;
}

void AttitudeWidget::setRoll(int roll)
{
    m_roll = roll;
}

void AttitudeWidget::setPitch(int pitch)
{
    m_pitch = pitch;
}

void AttitudeWidget::setWantedRoll(int roll)
{
    m_wantedRoll = roll;
}

void AttitudeWidget::setWantedPitch(int pitch)
{
    m_wantedPitch = pitch;
}

void AttitudeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter.translate(width()/2, height()/2 + 2 * m_pitch);
    painter.rotate(m_roll * 0.8);

    QPainterPath skyPath(QPointF(-width(), -height()*2));
    skyPath.lineTo(QPointF(width()*2, -height()*2));
    skyPath.lineTo(QPointF(width()*2, 0));
    skyPath.lineTo(QPointF(-width(), 0));
    skyPath.closeSubpath();
    QLinearGradient skyGradient(0, -height()/2, 0, 0);
    skyGradient.setColorAt(0, QColor::fromHsvF(0.6, 1.0, 0.7));
    skyGradient.setColorAt(1, QColor::fromHsvF(0.6, 0.25, 0.9));
    QBrush skyBrush(skyGradient);
    painter.fillPath(skyPath, skyBrush);

    QPainterPath groundPath(QPointF(width()*2, height()*3));
    groundPath.lineTo(-width(), height()*3);
    groundPath.lineTo(-width(), 0);
    groundPath.lineTo(width()*2, 0);
    groundPath.closeSubpath();
    QLinearGradient groundGradient(0, height()/2, 0, 0);
    groundGradient.setColorAt(0, QColor::fromHsvF(0.25, 1, 0.5));
    groundGradient.setColorAt(1, QColor::fromHsvF(0.25, 0.25, 0.5));
    QBrush groundBrush(groundGradient);
    painter.fillPath(groundPath, groundBrush);

    QPen pen;
    pen.setWidthF(2);
    pen.setColor(QColor(255, 255, 255));
    painter.setPen(pen);
    QPoint start(-width(), 0);
    QPoint end(width()*2, 0);
    painter.drawLine(start, end);

    painter.resetTransform();
    painter.translate(width()/2, height()/2 + 2 * m_wantedPitch);
    painter.rotate(m_wantedRoll * 0.8);

    pen.setColor(QColor(10, 10, 10));
    painter.setPen(pen);
    QPoint start2(-30, 0);
    QPoint end2(30, 0);
    painter.drawLine(start2, end2);

    painter.end();
}
