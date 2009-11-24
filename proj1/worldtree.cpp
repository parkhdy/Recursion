#include <QPainter>

#include "worldtree.h"

worldTree::worldTree(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(250, 250, 200)));
  setAutoFillBackground(true);
}
