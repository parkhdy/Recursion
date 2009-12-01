#include <QPainter>

#include "worldspace.h"

worldSpace::worldSpace(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);
  cXpos = 12;
  cYpos = 12;
  
  //Initalizes the "permanent" vectors to the correct size.
  rockmap = std::vector<std::vector<char> > (ROW, std::vector<char>(COL,'n'));
  slice = std::vector<std::vector<char> > (WINSIZE, 
                                           std::vector<char>(WINSIZE,'n'));

  //Initalizes the "impermanent" vectors to the correct size.
  lvl1 = std::vector<std::vector<char> > (ROW, std::vector<char>(COL, 'g'));

  //Initalize the down portal, the up portal and some terrain features.
  lvl1[12][20] = 'd';
  lvl1[12][22] = 'u';
  lvl1[18][18] = 'i';
  
  //Make a small pool of water.
  lvl1[20][20] = 'w';
  lvl1[20][21] = 'w';
  lvl1[21][20] = 'w';
  lvl1[21][21] = 'w';

  //Initalizes the "rock map"
  //Figure out a way to make this a static dec.
  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {
          if(r == 5 && (c < 10 || c > 15))
            rockmap[c][r] = 'r';
          else
            rockmap[c][r] = 'n';
        }
    }

  //The default clvl, or current level, is level 1.
  clvl = lvl1;

  updateSlice();
  update();
}

void worldSpace::moveUP()
{
  cdir = 0;
  moveChar(cdir);
}

void worldSpace::moveDOWN()
{
  cdir = 1;
  moveChar(cdir);
}

void worldSpace::moveLEFT()
{
  cdir = 3;
  moveChar(cdir);
}

void worldSpace::moveRIGHT()
{
  cdir = 2;
  moveChar(cdir);
}

void worldSpace::updateSlice()
{
  //Check the rockmap against the current terrain to see if there are any
  //Rocks over a water tile. If there are, destroy the rock and the water
  //Tile.
  for(int r = 0; r < ROW; r++)
    {
      for(int c = 0; c < COL; c++)
        {
          if(clvl[r][c] == 'w' && rockmap[r][c] == 'r')
            {
              clvl[r][c] = 'g';
              rockmap[r][c] = 'n';
            }
        }
    }

  //Update Slice with the current terrain.
  int r2 = 0;
  for(int r = cXpos-12; r < cXpos+13; r++)
    {
      int c2 = 0;
      for(int c = cYpos-12; c < cYpos+13; c++)
        {
          //If r is less than 0 or more than ROW/COL, it's off the map.
          //Update Slice with a 'n' or null tile. Otherwise, update it
          //with what's currently there.
          if((r >= 0 && r < ROW) && (c >= 0 && c < COL))
            slice[r2][c2] = clvl[r][c];
          else
            slice[r2][c2] = 'n';
          c2 = c2 + 1;
        }
      r2 = r2 + 1;
    }

  //Update slice with the rockmap.
  r2 = 0;
  for(int r = cXpos-12; r < cXpos+13; r++)
    {
      int c2 = 0;
      for(int c = cYpos-12; c < cYpos+13; c++)
        {
          if((r >= 0 && r < ROW) && (c >= 0 && c < COL) 
             && (rockmap[r][c] == 'r'))
            slice[r2][c2] = rockmap[r][c];
          c2 = c2 + 1;
        }
      r2 = r2 + 1;
    }
  
  emit sendMap(prepMap());
}

//Prepares a map to send.
std::vector<std::vector<char> > worldSpace::prepMap()
{
  std::vector<std::vector<char> > preppedMap;
  preppedMap = clvl;
  //Updates a new array representing the map with the rockmap for reference. 
  //Should also probably show where the player is. I can easily add this.
  for(int r = 0; r < ROW; r++)
    {
      for (int c = 0; c < COL; c++)
        {
          if(rockmap[r][c] == 'r')
            preppedMap[r][c] = 'r';
          if(r == cXpos && c == cYpos)
            preppedMap[r][c] = 'p';
        }
    }

  return preppedMap;
}

void worldSpace::moveChar(int dir)
{
  //Move Up / North
  if(dir == 0)
    {
      if(cYpos == 0)
        return;
      if(traversable(cdir))
        cYpos -= 1;
      else if(!traversable(cdir) && canPush(cdir))
        {
          push(cdir);
          cYpos -= 1;
        }
    }
  //Move down / south
  else if(dir == 1)
    {
      if(cYpos >= COL-1)
        return;
      if(traversable(cdir))
        cYpos += 1;
      else if(!traversable(cdir) && canPush(cdir))
        {
          push(cdir);
          cYpos += 1;
        }
    }
  //Move right / east
  else if(dir == 2)
    {
      if(cXpos >= ROW-1)
        return;
      if(traversable(cdir))
        cXpos += 1;
      else if(!traversable(cdir) && canPush(cdir))
        {
          push(cdir);
          cXpos += 1;
        }
    }
  //move left / west
  else if(dir == 3)
    {
      if(cXpos == 0)
        return;
      if(traversable(cdir))
        cXpos -= 1;
      else if(!traversable(cdir) && canPush(cdir))
        {
          push(cdir);
          cXpos -= 1;
        }
    }
  update();
  emit moved();
}

void worldSpace::paintEvent(QPaintEvent *)
{
  //Paints Slice, which is the area of the world that's
  //visible to us.
  QPainter painter(this);

  for(int r = 0; r < WINSIZE; r++)
    {
      for(int c = 0; c < WINSIZE; c++)
        {
          paintTile(painter, r, c, slice[r][c]);
        }
    }

  //Draws the red rectangle that indicates the player.
  //The player will always be located in the center of the screen.
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(12*TILESIZE, 12*TILESIZE,
                         TILESIZE, TILESIZE));
}

bool worldSpace::canPush(int dir)
{
  if(dir == 0)
    {
      if (cYpos-2 >= 0
          && clvl[cXpos][cYpos-1] != 'i' && clvl[cXpos][cYpos-1] != 'w'
          && clvl[cXpos][cYpos-2] != 'i' 
          && rockmap[cXpos][cYpos-2] == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 1)
    {
      if (cYpos+2 < COL
          && clvl[cXpos][cYpos+1] != 'i' && clvl[cXpos][cYpos+1] != 'w'
          && clvl[cXpos][cYpos+2] != 'i'
          && rockmap[cXpos][cYpos+2] == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 2)
    {
      if (cXpos+2 < ROW
          && clvl[cXpos+1][cYpos] != 'i' && clvl[cXpos+1][cYpos] != 'w'
          && clvl[cXpos+2][cYpos] != 'i' 
          && rockmap[cXpos+2][cYpos] == 'n')
        return true;
      else
        return false;
    }
  else //Dir == 3
    {
      if (cXpos-2 >= 0
          && clvl[cXpos-1][cYpos] != 'i' && clvl[cXpos-1][cYpos] != 'w'
          && clvl[cXpos-2][cYpos] != 'i'
          && rockmap[cXpos-2][cYpos] == 'n')
        return true;
      else
        return false;
    }
}

void worldSpace::push(int dir)
{
  //Push a rock north
  if(dir == 0)
    {
      rockmap[cXpos][cYpos-1] = 'n';
      rockmap[cXpos][cYpos-2] = 'r';
    }
  //Push a rock south
  else if(dir == 1)
    {
      rockmap[cXpos][cYpos+1] = 'n';
      rockmap[cXpos][cYpos+2] = 'r';
    }
  //Push a rock east / right
  else if(dir == 2)
    {      
      rockmap[cXpos+1][cYpos] = 'n';
      rockmap[cXpos+2][cYpos] = 'r';       
    }
  //Push a rock west / left
  else //Dir == 3
    {     
      rockmap[cXpos-1][cYpos] = 'n';
      rockmap[cXpos-2][cYpos] = 'r';
    }
}

bool worldSpace::traversable(int dir)
{
  //0 = Up, 1 = Down, 2 = Right, 3 = Left
  //This will return true if the square immediately to the
  //Direction the player wishes to go is unoccupied by a rock
  //a "tree" or water.
  //Creates an interesting problem with being a boolean value.
  //Any terrain that isn't passable can have a rock pushed right
  //out of it. Really weird.
  if(dir == 0)
    {
      if( clvl[cXpos][cYpos-1] != 'i' 
          && clvl[cXpos][cYpos-1] != 'w'
          && rockmap[cXpos][cYpos-1] == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 1)
    {
      if( clvl[cXpos][cYpos+1] != 'i' 
          && clvl[cXpos][cYpos+1] != 'w'
          && rockmap[cXpos][cYpos+1] == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 2)
    {
     if( clvl[cXpos+1][cYpos] != 'i' 
         && clvl[cXpos+1][cYpos] != 'w'
         && rockmap[cXpos+1][cYpos] == 'n')
        return true;
      else
        return false;
    }
  else //Dir == 3
    {
      if( clvl[cXpos-1][cYpos] != 'i'
          && clvl[cXpos-1][cYpos] != 'w'
          && rockmap[cXpos-1][cYpos] == 'n')
        return true;
      else
        return false; 
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
  else if(type == 'n')
    painter.setBrush(Qt::black);
  else if(type == 'd')
    painter.setBrush(QColor(250, 25, 150));
  else if(type == 'u')
    painter.setBrush(QColor(250, 150, 25));
  else if(type == 'i')
    painter.setBrush(QColor(0, 125, 0));
  else if(type == 'w')
    painter.setBrush(Qt::blue);
    
  painter.drawRect(currentTile(row, col));
}

QRect worldSpace::currentTile(int grow, int gcol)
{
  return QRect(grow * TILESIZE, gcol * TILESIZE, 
               TILESIZE, TILESIZE);
}
