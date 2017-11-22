#include "variable.h"

Variable::Variable(QString expression, bool getter, bool setter, bool prefix) :
  m_generateGetter(getter), m_generateSetter(setter)
{
  QStringList m_parsedAttribute = expression.split(' ', QString::SkipEmptyParts);
  m_prefixed_variable = m_parsedAttribute.last();
  m_variable = m_prefixed_variable;
  m_parsedAttribute.pop_back();
  m_type = m_parsedAttribute.last();
  m_parsedAttribute.pop_back();
  if (!m_parsedAttribute.isEmpty())
    {
    m_keywords = m_parsedAttribute.join(' ');
    m_keywords.push_front("  ");
    m_keywords.push_back(" ");
    }
  else
    m_keywords = "";

  if(prefix)
    m_prefixed_variable.push_front("m_");
}

void Variable::addToList(QListWidget *list)
{
  list->addItem("[" + m_keywords + " " + m_type + " ] : " + m_prefixed_variable);
}

void Variable::addToCode(QString& publicBlock, QString& privateBlock)
{
  privateBlock +=  m_keywords + m_type +" " + m_prefixed_variable + ";\n";

  if (m_generateGetter)
    {
      m_variable[1].toUpper();
      publicBlock += "  " + m_type + " get" + m_variable + "() const { return " + m_prefixed_variable + " };\n";
      m_variable[1].toLower();
    }

  if (m_generateSetter)
    {
      m_variable[1].toUpper();
      publicBlock +="  void set" + m_variable + "( " + m_type + " val) { "
                + m_prefixed_variable + " = val; };\n";
      m_variable[1].toLower();
    }
}
