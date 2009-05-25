/*
    Copyright (c) 2009 Stephen Kelly <steveire@gmail.com>
*/

#ifndef CYCLENODE_H
#define CYCLENODE_H

#include "node.h"
#include "interfaces/taglibraryinterface.h"


using namespace Grantlee;


class CycleNodeFactory : public AbstractNodeFactory
{
  Q_OBJECT
public:
  CycleNodeFactory();

  Node* getNode(const QString &tagContent, Parser *p, QObject *parent) const;

};

/**
Cycles endlessly over elements.
*/
template <typename T>
class RingIterator
{
public:
  RingIterator<T>(QList<T> list)
  : m_it(list)
  {
    Q_ASSERT(list.size() > 0);
  }

  /**
  Returns the next element in the list, or the first element if already
  at the last element.
  */
  T next()
  {
    if (m_it.hasNext())
    {
      T item = m_it.next();
      return item;
    }
    m_it.toFront();
    return m_it.next();
  }

private:
  QListIterator<T> m_it;
};

class CycleNode : public Node
{
  Q_OBJECT
public:
  CycleNode(QList<FilterExpression> list, const QString &name, QObject *parent);

  QString render(Context *c);

private:
  RingIterator<FilterExpression> m_variableIterator;
  QString m_name;

};

#endif
