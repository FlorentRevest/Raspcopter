#ifndef SCRIPTTOOL_H
#define SCRIPTTOOL_H

#include "ui_scripttool.h"

class ScriptTool: public QWidget, public Ui::ScriptForm
{
  Q_OBJECT
  public:
      ScriptTool(QWidget * parent = NULL);

      void setPath(const QString & path);
  protected slots:
    void setScript();
    void setPath();
    void updatePValue();
    void updatePValue(const QString & );

    void rescale();
    void resize();

  protected:
     void init();
     void resizeEvent(QResizeEvent * event);

}; // class ScriptTool

#endif // SCRIPTTOOL_H
