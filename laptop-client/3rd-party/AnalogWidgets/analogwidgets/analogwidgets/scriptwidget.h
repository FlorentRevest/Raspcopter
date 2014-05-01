/***************************************************************************
 *   Copyright (C) 2006-2008 by Tomasz Ziobrowski                          *
 *   http://www.3electrons.com                                             *
 *   e-mail: t.ziobrowski@3electrons.com                                   *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef SCRIPTWIDGET_H
#define SCRIPTWIDGET_H
#include <QGraphicsView>
#include <QVariant>
#include <QMap>
#include <QSet>

class QGraphicsScene;
class QScriptEngine;
class QSvgRenderer;

class ScriptWidget: public QGraphicsView
{
  Q_OBJECT
  Q_PROPERTY (QString  script READ script    WRITE setScript)
  Q_PROPERTY (QVariant PValue READ getPValue WRITE setPValue DESIGNABLE false STORED false)
  Q_PROPERTY (QString  PName  READ getPName  WRITE setPName  DESIGNABLE false STORED false)
  public:
    ScriptWidget(QWidget * parent = NULL);
    ScriptWidget(const QString & objectName, QWidget * parent = NULL);
    ~ScriptWidget();
    QString     script() const;
    QString     svgFile() const;
    QVariant    getPValue() const;
    QString     getPName() const; 
    QStringList PNames() const; 

  signals:

    void evaluate();

  public slots:
    void setScript(const QString & s);
    void setSvgFile(const QString & file); 
    void addItem(const QString & name);
    void resetItems(); 
    void loadSvgFile(const QString & file);

    void setPName(const QString & name);

    void setPValue(int);
    void setPValue(double); 
    void setPValue(const QString & );
    void setPValue(const QVariant & );
    

  protected slots:

  protected:
    void init();
    void clearSvgItems();
    void resizeEvent ( QResizeEvent * ); 
    

    QGraphicsScene        * m_scene;
    static QScriptEngine  * m_engine;
    QSvgRenderer          * m_renderer;
    QString                 m_script;
    QString                 m_svgFile;
    QSet<QString>           m_items;
    QString                 m_currentProperty;
    QMap<QString,QVariant>  m_values;
  public:

}; // class ScriptWidget

#endif // SCRIPTWIDGET_H
