#ifndef WORLDTREE_H
#define WORLDTREE_H

#include <QWidget>

#include "defs.h"

class worldTree : public QWidget
{
  Q_OBJECT

  public:
  worldTree(QWidget *parent = 0);

public slots:
  void updateTree(int clvl);

protected:
  void paintEvent(QPaintEvent *event);

private:
  void paintRect(QPainter &painter,
                 int row);

  QRect currentTile(int grow);

  int culvl;
};

#endif
