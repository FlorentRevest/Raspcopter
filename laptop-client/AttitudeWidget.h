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
