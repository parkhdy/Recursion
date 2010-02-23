#include <QPainter>

#include "worldtree.h"

worldTree::worldTree(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  culvl = 1;
}

void worldTree::updateTree(int clvl)
{
  culvl = clvl;
  update();
}

void worldTree::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  for(int r = 0; r < 3; r++)
    paintRect(painter, r);

  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(TILESIZE, ((culvl*20)),
                         TILESIZE-5, TILESIZE-5));
}

void worldTree::paintRect(QPainter &painter,
                          int row)
{
  painter.setPen(Qt::NoPen);

  painter.setBrush(Qt::green);

  painter.drawRect(currentTile(row));
}

QRect worldTree::currentTile(int grow)
{
  int xoff = 20;
  int yoff = 20;

  return QRect(((TILESIZE)+xoff), ((grow * TILESIZE)+yoff),
               TILESIZE+50, TILESIZE-5);
}
