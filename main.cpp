#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  mainWindow myMainWindow;
  myMainWindow.show();
  return app.exec();
}
