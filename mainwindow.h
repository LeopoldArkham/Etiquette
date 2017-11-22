#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckbox>
#include <QDateEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QGroupBox>
#include <vector>
#include <variable.h>

class mainWindow : public QWidget
{
  Q_OBJECT
public:
  mainWindow();

public slots:
  void addVariable();
  void removeVariable();
  void generateCode();

private:
  // Class Info
  QLineEdit *className;
  QLineEdit *classInherits;

  // Inclusions
  QCheckBox *multipleInclusions;
  QLineEdit *headerGuardStructure;
  QCheckBox *defaultConstructor;
  QCheckBox *destructor;
  QCheckBox *QObjectMacro;
  QCheckBox *generateCounter;

  // Comments
  QLineEdit *author;
  QTextEdit *classDescription;
  QGroupBox *commentsGroupBox;

  // Attributes
  QLineEdit *variable;
  QCheckBox *generateGetter;
  QCheckBox *generateSetter;
  QCheckBox *prefix;
  QListWidget *variablesList;
  std::vector<Variable> variableVector;

  // File Policy
  QCheckBox *generateHeaderFile;
  QCheckBox *generateSourceFile;
  QLineEdit *headerFilePath;
  QLineEdit *sourceFilePath;
  QCheckBox *noCaps;


};

#endif // MAINWINDOW_H
