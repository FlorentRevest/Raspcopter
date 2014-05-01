#ifndef SVGFILETASKMENU_H
#define SVGFILETASKMENU_H

#include <QtDesigner> 
#include <QDesignerTaskMenuExtension>
#include <QExtensionFactory>

class QAction;


class SvgFileTaskMenu : public QObject, public QDesignerTaskMenuExtension
{
     Q_OBJECT
     Q_INTERFACES(QDesignerTaskMenuExtension)

 public:
     SvgFileTaskMenu(QWidget *widget, QObject *parent);

    
     QAction *preferredEditAction() const;
     QList<QAction *> taskActions() const;

 private slots:
     void setSvgFile();
     

 private:
     bool openFile(QString & fileName); 
     
     QWidget *m_widget;
     QAction *m_setSvgFile;
};

 
/* FACTORY */
class SvgFileTaskMenuFactory : public QExtensionFactory
{
    Q_OBJECT
public:
    SvgFileTaskMenuFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

 

#endif // SVGFILETASKMENU_H
