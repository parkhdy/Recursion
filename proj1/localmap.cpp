#include <QPainter>

#include "localmap.h"

localMap::localMap(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  cmap = std::vector<std::vector<char> > (ROW, std::vector<char>(COL, 'n'));
}

void localMap::updateMap(std::vector<std::vector<char> > nextmap)
{
  cmap = nextmap;
  update();
}

void localMap::paintEvent(QPaintEvent *)
{
  //Paints the entire world.
  QPainter painter(this);

  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {
          paintTile(painter, r, c, cmap[c][r]);
        }
    }
  
  //Draws the red rectangle that indicates the player.
  //The player will always be located in the center of the screen.
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(12*TILESIZE, 12*TILESIZE,
                         TILESIZE, TILESIZE));

}

void localMap::paintTile(QPainter &painter, 
                           int row, int col, 
                           char type)
{
  painter.setPen(Qt::NoPen);

  if(type == 'g')
    painter.setBrush(Qt::green);
  else if(type == 'r')
    painter.setBrush(Qt::gray);
  else if(type == 'n')
    painter.setBrush(Qt::black);
  else if(type == 'd')
    painter.setBrush(QColor(250, 25, 150));
  else if(type == 'u')
    painter.setBrush(QColor(250, 150, 25));
  else if(type == 'p')
    painter.setBrush(Qt::red);
  else if(type == 'i')
    painter.setBrush(QColor(0, 125, 0));
  else if(type == 'w')
    painter.setBrush(Qt::blue);
    
  painter.drawRect(currentTile(row, col));
}

QRect localMap::currentTile(int grow, int gcol)
{
  int xoff = 10;
  int yoff = 50;

  return QRect(((grow * STILESIZE)+xoff), ((gcol * STILESIZE)+yoff), 
               STILESIZE, STILESIZE);
}
