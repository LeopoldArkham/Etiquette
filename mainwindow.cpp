#include <QLabel>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include "outputwindow.h"
#include "mainwindow.h"

mainWindow::mainWindow() :
  QWidget()
{
  setWindowTitle("C++ Class Generator");
  resize(650, 500);

  // Create Info section

  className = new QLineEdit;
  classInherits = new QLineEdit;

  QFormLayout *classInfoFormLayout = new QFormLayout;
  classInfoFormLayout->addRow("Class name:", className);
  classInfoFormLayout->addRow("Inherits:", classInherits);

  QGroupBox *classInfoGroupBox = new QGroupBox;
  classInfoGroupBox->setTitle("Class information");
  classInfoGroupBox->setLayout(classInfoFormLayout);

  // Create inclusions section

  multipleInclusions = new QCheckBox("Protect header against multipe inclusions");
  multipleInclusions->setChecked(true);
  QLabel *headerGuardLabel = new QLabel("Header guard template:");
  headerGuardStructure = new QLineEdit;
  headerGuardStructure->setText("%class_DEFINED");
  defaultConstructor = new QCheckBox("Generate constructor");
  defaultConstructor->setChecked(true);
  destructor = new QCheckBox("Generate destructor");
  QObjectMacro = new QCheckBox("Insert QObject macro");
  generateCounter = new QCheckBox("Generate counter");

  QGridLayout *inclusionsLayout = new QGridLayout;
  inclusionsLayout->addWidget(multipleInclusions, 0, 0, 1, 2);
  inclusionsLayout->addWidget(headerGuardLabel, 1, 0);
  inclusionsLayout->addWidget(headerGuardStructure, 1, 1);
  inclusionsLayout->addWidget(defaultConstructor, 2, 0);
  inclusionsLayout->addWidget(generateCounter, 2, 1);
  inclusionsLayout->addWidget(destructor, 3, 0);
  inclusionsLayout->addWidget(QObjectMacro, 3, 1);

  QGroupBox *inclusionsGroupBox = new QGroupBox;
  inclusionsGroupBox->setTitle("Include and generate");
  inclusionsGroupBox->setLayout(inclusionsLayout);

  //Comments

  QLabel *authorLabel = new QLabel("Author:");
  QLabel *classDescriptionLabel = new QLabel("Class description:");
  author = new QLineEdit;
  classDescription = new QTextEdit;

  QGridLayout *commentsLayout = new QGridLayout;
  commentsLayout->addWidget(authorLabel, 0, 0);
  commentsLayout->addWidget(author, 0, 1);
  commentsLayout->addWidget(classDescriptionLabel, 1, 0);
  commentsLayout->addWidget(classDescription, 2, 0, 1, 2);

  commentsGroupBox = new QGroupBox;
  commentsGroupBox->setCheckable(true);
  commentsGroupBox->setTitle("Comments");
  commentsGroupBox->setLayout(commentsLayout);

  //Attributes

  variable = new QLineEdit;
  QPushButton *add = new QPushButton("Add");
  add->setMaximumWidth(35);
  generateGetter = new QCheckBox("Generate getter method");
  generateSetter = new QCheckBox("Generate setter method");
  generateGetter->setChecked(true);
  prefix = new QCheckBox("Add \"_m\" prefix");
  prefix->setChecked(true);
  variablesList = new QListWidget;
  QPushButton *removeVariable = new QPushButton("Remove");

 QHBoxLayout *attributesHBox1 = new QHBoxLayout;
 attributesHBox1->addWidget(variable);
 attributesHBox1->addWidget(add);

 QGridLayout *attributesGrid = new QGridLayout;
 attributesGrid->addWidget(generateGetter, 0, 0);
 attributesGrid->addWidget(generateSetter, 0, 1);
 attributesGrid->addWidget(prefix, 1, 0);

 QGridLayout *attributesGrid2 = new QGridLayout;
 attributesGrid2->addWidget(variablesList, 0, 0, 1, 3);
 attributesGrid2->addWidget(removeVariable, 1, 1);

 QVBoxLayout *attributesLayout = new QVBoxLayout;
 attributesLayout->addLayout(attributesHBox1);
 attributesLayout->addLayout(attributesGrid);
 attributesLayout->addLayout(attributesGrid2);

  QGroupBox *attributesGroupBox = new QGroupBox;
  attributesGroupBox->setTitle("Add new:");
  attributesGroupBox->setLayout(attributesLayout);

  //File Policy

  QLabel *headerPathLabel = new QLabel("Header file:");
  QLabel *sourcePathLabel = new QLabel("Source file:");
  generateHeaderFile = new QCheckBox();
  generateSourceFile = new QCheckBox("  ");
  headerFilePath = new QLineEdit;
  sourceFilePath = new QLineEdit;
  QPushButton *selectHeaderFilePath = new QPushButton("...");
  selectHeaderFilePath->setMaximumWidth(25);
  QPushButton *selectSourceFilePath = new QPushButton("...");
  selectSourceFilePath->setMaximumWidth(25);
noCaps = new QCheckBox("File names are all lower-case");

  QGridLayout *filePolicyLayout = new QGridLayout;
  filePolicyLayout->setSpacing(1);
  filePolicyLayout->addWidget(headerPathLabel, 0, 0, 1, 3);
  filePolicyLayout->addWidget(generateHeaderFile, 1, 0);
  filePolicyLayout->addWidget(headerFilePath, 1, 1);
  filePolicyLayout->addWidget(selectHeaderFilePath, 1, 2);
  filePolicyLayout->addWidget(sourcePathLabel, 2, 0, 1, 3);
  filePolicyLayout->addWidget(generateSourceFile, 3, 0);
  filePolicyLayout->addWidget(sourceFilePath, 3, 1);
  filePolicyLayout->addWidget(selectSourceFilePath, 3, 2);
  filePolicyLayout->addWidget(noCaps, 4, 0, 1, 3);

  QGroupBox *filePolicyGroupBox = new QGroupBox(this);
  filePolicyGroupBox->setTitle("File Policy");
  filePolicyGroupBox->setLayout(filePolicyLayout);

  // Create main layout

  QVBoxLayout *vbox1 = new QVBoxLayout;
  vbox1->addWidget(classInfoGroupBox);
  vbox1->addWidget(inclusionsGroupBox);
  vbox1->addWidget(commentsGroupBox);

  QPushButton *generateCodeButton = new QPushButton("Generate");

  QVBoxLayout *vbox2 = new QVBoxLayout;
  vbox2->addWidget(attributesGroupBox);
  vbox2->addWidget(filePolicyGroupBox);
  vbox2->addWidget(generateCodeButton);
  //vbox2->addStretch(1);

  QHBoxLayout *hbox = new QHBoxLayout(this);
  hbox->addLayout(vbox1);
  hbox->addLayout(vbox2);

  //Connect

  connect(add, SIGNAL(clicked()), this, SLOT(addVariable()));
  connect(variable, SIGNAL(returnPressed()), this, SLOT(addVariable()));
  connect(removeVariable, SIGNAL(clicked()), this, SLOT(removeVariable()));
  connect(generateCodeButton, SIGNAL(clicked()), this, SLOT(generateCode()));
}

// Slots

void mainWindow::addVariable()
{
  if(!variable->text().isEmpty())
    {
      Variable var(variable->text(), generateGetter->isChecked(),
                   generateSetter->isChecked(), prefix->isChecked());
      variableVector.push_back(var);
      var.addToList(variablesList);
    }
}

void mainWindow::removeVariable()
{
    unsigned int current(variablesList->currentRow());

    if(current != 4294967295U)
      {
        variableVector.erase(variableVector.begin() + current);
        variablesList->takeItem(current);
      }
}

void mainWindow::generateCode()
{
  if(className->text().isEmpty())
    {
      QMessageBox::warning(this, "Missing field", "'Class Name' cannot be empty.");
      return;
    }

  QString code;

  if(commentsGroupBox->isChecked())
    {
      code += "/*\nClass " + className->text();

      if(!classInherits->text().isEmpty())
        code += ", inherits"  + classInherits->text();

      code += "\nAuthor: " + author->text() + "\n";
      code += "Created: " + QDate::currentDate().toString() + "\n\n";
      code += classDescription->toPlainText() + "\n*/\n\n";
    }

if(multipleInclusions->isChecked())
  {
    QString def(headerGuardStructure->text().replace("%class", className->text().toUpper()));
    code += "#ifndef " + def + "\n#define " + def + "\n\n";
  }

code += "class " + className->text();

if(!classInherits->text().isEmpty())
{
  code += " : public " + classInherits->text();
}

code += "\n{\n";

if(QObjectMacro->isChecked())
  code += "  Q_OBJECT\n";

QString publicBlock, privateBlock;

publicBlock += "public:\n";
if(defaultConstructor->isChecked())
  publicBlock += "  " + className->text() + "();\n";

privateBlock += "private:\n";

for (Variable v : variableVector)
  v.addToCode(publicBlock, privateBlock);

code += publicBlock + "\n";
code += privateBlock + "\n";

code += "}\n\n";

if(multipleInclusions->isChecked())
    code += "#endif ";

outputWindow *out = new outputWindow(code, this);
out->exec();
}
