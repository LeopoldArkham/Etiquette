#include "outputwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

outputWindow::outputWindow(QString &code, QWidget *parent) :
  QDialog(parent)
{
  QTextEdit *outputCode = new QTextEdit;
  outputCode->setPlainText(code);
  outputCode->setReadOnly(true);
  outputCode->setFont(QFont("Courrier"));
  outputCode->setLineWrapMode(QTextEdit::NoWrap);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(outputCode);

  resize(350, 450);
  setLayout(vbox);

}
