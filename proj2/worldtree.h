#ifndef WORLDTREE_H
#define WORLDTREE_H

#include <QWidget>
#include <sstream>

#include "defs.h"
#include "unit.h"

class worldTree : public QWidget
{
  Q_OBJECT

  public:
  worldTree(QWidget *parent = 0);

public slots:
  void updateTree(unit uni);

protected:
  void paintEvent(QPaintEvent *event);

private:
  void paintRect(QPainter &painter,
                 int row);
  const char* conversion(int number);

  QRect currentTile(int grow);

  int culvl;
  unit cunit;
};

#endif
