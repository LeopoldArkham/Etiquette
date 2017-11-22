#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QDialog>

class outputWindow : public QDialog
{
  Q_OBJECT
public:
  outputWindow(QString &code, QWidget *parent);
private:
};

#endif // OUTPUTWINDOW_H
