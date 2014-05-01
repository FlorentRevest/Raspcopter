#include <QResizeEvent>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "scripttool.h"


ScriptTool::ScriptTool(QWidget * parent ):QWidget(parent)
{
  init();
}

void ScriptTool::setScript()
{
  qDebug("ScriptTool::setScript");

  qDebug("ScriptTool::loadScript()");
  QString fileName = fileEdit->text();
  if (!fileName.isEmpty())
      scriptWidget->setScript(fileName  );


  PCombo->clear();
  PCombo->addItems(scriptWidget->PNames());
  updatePValue();
}


void ScriptTool::setPath()
{
  setPath(QFileDialog::getOpenFileName(this,trUtf8("Open file"),QString(),trUtf8("(Qt Script *.qjs)")));
}

void ScriptTool::updatePValue()
{
   QString name = scriptWidget->getPName();
   scriptWidget->setPName(PCombo->currentText());
   PLabel->setText(scriptWidget->getPValue().toString());
   scriptWidget->setPName(name);
}

void ScriptTool::updatePValue(const QString & text)
{
  QString name = scriptWidget->getPName();
   scriptWidget->setPName(text);
   PLabel->setText(scriptWidget->getPValue().toString());
  scriptWidget->setPName(name);
}

void ScriptTool::setPath(const QString & path ) 
{
     fileEdit->setText(path);
}

void ScriptTool::rescale()
{
   valueSlider->setMinimum(minSpinBox->value());
   valueSlider->setMaximum(maxSpinBox->value());
}

void ScriptTool::resize()
{
  scriptWidget->resize(horizontalSlider->value(),verticalSlider->value());
}

void ScriptTool::init()
{
  setupUi(this);
  connect(horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(resize()));
  connect(verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(resize()));
  connect(minSpinBox,SIGNAL(valueChanged(int)),this,SLOT(rescale()));
  connect(maxSpinBox,SIGNAL(valueChanged(int)),this,SLOT(rescale()));
  connect(setButton,SIGNAL(clicked()),this,SLOT(setScript()));
  connect(fileButton,SIGNAL(clicked()),this,SLOT(setPath()));
  connect(scriptWidget,SIGNAL(evaluate()),this,SLOT(updatePValue()));
  connect(PCombo,SIGNAL(highlighted(const QString &)),this,SLOT(updatePValue(const QString &)));
  resizeEvent(NULL);
  horizontalSlider->setValue(100);
  verticalSlider->setValue(100);
}

void ScriptTool::resizeEvent(QResizeEvent * )
{
  horizontalSlider->setMaximum(frame->width()-5);
  verticalSlider->setMaximum(frame->height()-5);
}
