#include <QtGui> 
#include <QFileDialog> 

#include "analogwidgets/counter.h" 
#include "analogwidgets/scriptwidget.h" 

#include "svgfile_taskmenu.h"


SvgFileTaskMenu::SvgFileTaskMenu(QWidget * w, QObject *parent)
    : QObject(parent)
{
    m_widget = w;

    m_setSvgFile = new QAction(tr("Set new svg resource file"), this);
 
    connect(m_setSvgFile  , SIGNAL(triggered()), this, SLOT(setSvgFile())); 
}


void SvgFileTaskMenu::setSvgFile()
{
  QString fileName ;
  Counter * w = qobject_cast<Counter *>(m_widget);
  if (w) 
  {
    if (openFile(fileName))
      w->setDigitsFile(fileName); 
  }
  ScriptWidget * s = qobject_cast<ScriptWidget*> (m_widget) ; 
  if (s) 
  {
    if (openFile(fileName))
      s->loadSvgFile(fileName); 
  }
}

bool SvgFileTaskMenu::openFile(QString & fileName)
{
    fileName = QFileDialog::getOpenFileName(0, trUtf8("Open Svg resource file"), QString(),
                                            trUtf8("Scalable Vector Graphics (*.svg *.SVG)")); 
    
    return !fileName.isEmpty(); 
}

QAction *SvgFileTaskMenu::preferredEditAction() const
{
    return m_setSvgFile;
}

QList<QAction *> SvgFileTaskMenu::taskActions() const
{
    QList<QAction *> list;
    list.append(m_setSvgFile);
    return list;
}


/*******************************************************************************************************/
 /* Screen Task Menu Factory */
SvgFileTaskMenuFactory::SvgFileTaskMenuFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}

QObject *SvgFileTaskMenuFactory::createExtension(QObject *object,
                                                   const QString &iid,
                                                   QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
        return 0;

    if (qobject_cast<Counter*>(object) || qobject_cast<ScriptWidget *> (object))
        return new SvgFileTaskMenu(qobject_cast<QWidget*>(object), parent);
    
    return 0;
}

