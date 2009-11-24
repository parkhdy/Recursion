#include <QPainter>

#include "worldspace.h"

worldSpace::worldSpace(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 250, 0)));
  setAutoFillBackground(true);
  cXpos = 100;
  cYpos = 100;
}

void worldSpace::moveUP()
{
  if(cYpos == 0)
    return;
  cYpos -= 10;
  update();
  emit movedY(0, cYpos);
}

void worldSpace::moveDOWN()
{
  if(cYpos >= (height()-10))
    return;
  cYpos += 10;
  update();
}

void worldSpace::moveLEFT()
{
  if(cXpos == 0)
    return;
  cXpos -= 10;
  update();
}

void worldSpace::moveRIGHT()
{
  if(cXpos >= (width()-10))
    return;
  cXpos += 10;
  update();
}

void worldSpace::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(cXpos, cYpos, 10, 10));
}
