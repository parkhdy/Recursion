#include <QPainter>

#include "localmap.h"

localMap::localMap(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);

  cmap = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'n')));
}

void localMap::updateMap(std::vector<std::vector<tile> > nextmap)
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
                           tile t1)
{
  painter.setPen(Qt::NoPen);

  if(t1.getType() == 'g')
    painter.setBrush(Qt::green);
  else if(t1.getType() == 'r')
    painter.setBrush(Qt::gray);
  else if(t1.getType() == 'n')
    painter.setBrush(Qt::black);
  else if(t1.getType() == 'd')
    painter.setBrush(QColor(250, 25, 150));
  else if(t1.getType() == 'u')
    painter.setBrush(QColor(250, 150, 25));
  else if(t1.getType() == 'p')
    painter.setBrush(Qt::red);
  else if(t1.getType() == 'i')
    painter.setBrush(QColor(0, 125, 0));
  else if(t1.getType() == 'w')
    painter.setBrush(Qt::blue);
    
  painter.drawRect(currentTile(row, col));
}

QRect localMap::currentTile(int grow, int gcol)
{
  int xoff = 20;
  int yoff = 65;

  return QRect(((grow * STILESIZE)+xoff), ((gcol * STILESIZE)+yoff), 
               STILESIZE, STILESIZE);
}
