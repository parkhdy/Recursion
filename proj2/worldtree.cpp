#include <QPainter>
#include <QPaintEvent>
#include <iostream>

#include "worldtree.h"

worldTree::worldTree(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(255, 255, 255)));
  setAutoFillBackground(true);

  culvl = 1;
}

void worldTree::updateTree(unit uni)
{
  cunit = uni;
  update();
  
  //std::cout << "Unit information acquired." << std::endl;
}

void worldTree::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  /*
  for(int r = 0; r < 3; r++)
    paintRect(painter, r);
  */

  QPen pen(Qt::black, 2, Qt::SolidLine);

  painter.setPen(pen);
  painter.setBrush(Qt::red);
  
  /*painter.drawRect(QRect(TILESIZE, ((culvl*20)),
    TILESIZE-5, TILESIZE-5));*/

  const char* name = cunit.getName().c_str();
  const char* title = cunit.getTitle().c_str();
  const char* health = conversion(cunit.getcHP());

  painter.setBrush(Qt::black);
  painter.setFont(QFont("Courier", 12, QFont::Bold));
  painter.drawText(20, 20, name);
  painter.drawText(20, 32, title);
  painter.drawText(20, 44, health);

  update();
}

void worldTree::paintRect(QPainter &painter,
                          int row)
{
  painter.setPen(Qt::NoPen);

  painter.setBrush(Qt::green);

  painter.drawRect(currentTile(row));
}

const char* worldTree::conversion(int number)
{
  std::ostringstream sin;
  sin << number;
  const char* val = sin.str().c_str();
  return val;
}

QRect worldTree::currentTile(int grow)
{
  int xoff = 20;
  int yoff = 20;

  return QRect(((TILESIZE)+xoff), ((grow * TILESIZE)+yoff),
               TILESIZE+50, TILESIZE-5);
}
