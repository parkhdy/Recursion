#include <QPainter>

#include "worldspace.h"

worldSpace::worldSpace(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);
  cXpos = 7;
  cYpos = 7;
  
  //Initalize level 1. Figure out a way to
  //Make this a static declaration later.
  for(int r = 0; r < ROW; r++)
    {
      for(int c = 0; c < COL; c++)
        {
          lvl1[r][c] = 'g';
          if(r == 5 && (c < 10 || c > 15))
            lvl1[r][c] = 'r';
        }
    }
}

void worldSpace::moveUP()
{
  cdir = 0;
  if(cYpos == 0)
    return;
  if(nextSpace(cdir) == 'g')
    cYpos -= 1;
  update();
  emit movedY(0, cYpos);
}

void worldSpace::moveDOWN()
{
  cdir = 1;
  if(cYpos >= (COL-1))
    return;
  if(nextSpace(cdir) == 'g')
    cYpos += 1;
  update();
  emit movedY(0, cYpos);
}

void worldSpace::moveLEFT()
{
  cdir = 3;
  if(cXpos == 0)
    return;
  if(nextSpace(cdir) == 'g')
    cXpos -= 1;
  update();
  emit movedX(0, cXpos);
}

void worldSpace::moveRIGHT()
{
  cdir = 2;
  if(cXpos >= (ROW-1))
    return;
  if(nextSpace(cdir) == 'g')
    cXpos += 1;
  update();
  emit movedX(0, cXpos);
}

void worldSpace::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  for(int r = cXpos-5; r < cXpos+6; r++)
    {
      for(int c = cYpos-5; c < cYpos+6; c++)
        {
          paintTile(painter, r, c, lvl1[r][c]);
        }
    }

  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(cXpos*TILESIZE, cYpos*TILESIZE,
                         TILESIZE, TILESIZE));
}

char worldSpace::nextSpace(int dir)
{
  //0 = Up, 1 = Down, 2 = Right, 3 = Left
  if(dir == 0)
    {
      return lvl1[cXpos][cYpos-1];
    }
  else if(dir == 1)
    {
      return lvl1[cXpos][cYpos+1];
    }
  else if(dir == 2)
    {
      return lvl1[cXpos+1][cYpos];
    }
  else //Dir == 3
    {
      return lvl1[cXpos-1][cYpos];
    }
}

void worldSpace::paintTile(QPainter &painter, 
                           int row, int col, 
                           char type)
{
  painter.setPen(Qt::NoPen);

  if(type == 'g')
    painter.setBrush(Qt::green);
  else if(type == 'r')
    painter.setBrush(Qt::gray);
    
  painter.drawRect(currentTile(row, col));
}

QRect worldSpace::currentTile(int grow, int gcol)
{
  return QRect(grow * TILESIZE, gcol * TILESIZE, 
               TILESIZE, TILESIZE);
}
