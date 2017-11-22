#ifndef VARIABLE_H
#define VARIABLE_H
#include <QString>
#include <QStringList>
#include <QListWidget>

class Variable
{
public:
  Variable(QString expression, bool getter, bool setter, bool prefix);
  void addToList(QListWidget *list);
  void addToCode(QString& publicBlock, QString& privateBlock);

private:
  QString m_variable;
  QString m_prefixed_variable;
  QString m_type;
  QString m_keywords;
  bool m_generateGetter;
  bool m_generateSetter;
};

#endif // VARIABLE_H
