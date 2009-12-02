#include <QPainter>
#include <iostream>

#include "worldspace.h"

worldSpace::worldSpace(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);
  cXpos = 12;
  cYpos = 12;
  onlvl = 1;
  
  //Initalizes the "permanent" vectors to the correct size.
  rockmap = std::vector<std::vector<char> > (ROW, std::vector<char>(COL,'n'));
  slice = std::vector<std::vector<char> > (WINSIZE, 
                                           std::vector<char>(WINSIZE,'n'));

  //Initalizes the "impermanent" vectors to the correct size.
  lvl1 = std::vector<std::vector<char> > (ROW, std::vector<char>(COL, 'g'));
  lvl2 = std::vector<std::vector<char> > (ROW, std::vector<char>(COL, 'g'));
  lvl3 = std::vector<std::vector<char> > (ROW, std::vector<char>(COL, 'g'));

  //Initalize the down portal, the up portal and some terrain features.
  //The fact that these are held in text files make for easy editing by me!
  //Thank god for small favors amirite?
  rockmap = cartographer.readLevel(0);
  lvl1 = cartographer.readLevel(1);

  //Initalize the up/down portal for level 2
  lvl2[6][8] = 'u';
  lvl2[12][14] = 'd';

  //Pool of water on level 2
  lvl2[20][19] = 'w';
  lvl2[20][20] = 'w';
  lvl2[20][21] = 'w';
  lvl2[21][20] = 'w';
  lvl2[21][21] = 'w';

  //Initalize the up/down portal for level 3
  lvl3[18][20] = 'u';
 

  //The default clvl, or current level, is level 1.
  clvl = lvl1;

  updateSlice();
  update();
}

//Old was 0 = up, 1 = down, 2 = right, 3 = left.
//I think I may have reversed this somehow...
//Which I can't wrap my head around.
//New is 3 = up, 2 = down, 1 = right, 0 = left.
//For some reason the vector structure is vec[y][x], which
//doesn't make all that much sense to me, frankly.
void worldSpace::moveUP()
{
  cdir = 3;
  moveChar(cdir);
}

void worldSpace::moveDOWN()
{
  cdir = 2;
  moveChar(cdir);
}

void worldSpace::moveLEFT()
{
  cdir = 0;
  moveChar(cdir);
}

void worldSpace::moveRIGHT()
{
  cdir = 1;
  moveChar(cdir);
}

void worldSpace::updateSlice()
{
  //Check the rockmap against the current terrain to see if there are any
  //Rocks over a water tile. If there are, destroy the rock and the water
  //Tile.
  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {
          if(clvl[c][r] == 'w' && rockmap[c][r] == 'r')
            {
              if(onlvl == 1)
                {
                  lvl1[c][r] = 'g';
                  clvl = lvl1;
                }
              else if(onlvl == 2)
                {
                  lvl2[c][r] = 'g';
                  clvl = lvl2;
                }
              else if(onlvl == 3)
                {
                  lvl3[c][r] = 'g';
                  clvl = lvl3;
                }

              rockmap[c][r] = 'n';
            }
        }
    }

  //Update Slice with the current terrain.
  int c2 = 0;
  for(int c = cXpos-12; c < cXpos+13; c++)
    {
      int r2 = 0;
      for(int r = cYpos-12; r < cYpos+13; r++)
        {
          //If r is less than 0 or more than ROW/COL, it's off the map.
          //Update Slice with a 'n' or null tile. Otherwise, update it
          //with what's currently there.
          if((r >= 0 && r < ROW) && (c >= 0 && c < COL))
            slice[c2][r2] = clvl[c][r];
          else
            slice[c2][r2] = 'n';
          r2 = r2 + 1;
        }
      c2 = c2 + 1;
    }

  //Update slice with the rockmap.
  c2 = 0;
  for(int c = cXpos-12; c < cXpos+13; c++)
    {
      int r2 = 0;
      for(int r = cYpos-12; r < cYpos+13; r++)
        {
          if((r >= 0 && r < ROW) && (c >= 0 && c < COL) 
             && (rockmap[c][r] == 'r'))
            slice[c2][r2] = rockmap[c][r];
          r2 = r2 + 1;
        }
      c2 = c2 + 1;
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
  for(int c = 0; c < COL; c++)
    {
      for (int r = 0; r < ROW; r++)
        {
          if(rockmap[c][r] == 'r')
            preppedMap[c][r] = 'r';
          if(c == cXpos && r == cYpos)
            preppedMap[c][r] = 'p';
        }
    }

  return preppedMap;
}

char worldSpace::onPortal()
{
  /*
  std::cout << "Checking to see if you're on a portal! Result is: " 
            << clvl[cXpos][cYpos]
            << std::endl;
  */
  return clvl[cXpos][cYpos];
}

void worldSpace::moveChar(int dir)
{
  //Move left / west
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
  //Move right / east
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
  //Move down / south
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
  //move up / north
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

  if(onPortal() == 'd')
    teleportal(0);
  else if(onPortal() == 'u')
    teleportal(1);

  /*
  if(lvl1 == lvl2)
    std::cout << "Level 1 is equal to level 2." << std::endl;
  else
    std::cout << "Level 1 and level 2 are different." << std::endl;
  */

  update();
  emit moved();
}

void worldSpace::paintEvent(QPaintEvent *)
{
  //Paints Slice, which is the area of the world that's
  //visible to us.
  QPainter painter(this);

  for(int c = 0; c < WINSIZE; c++)
    {
      for(int r = 0; r < WINSIZE; r++)
        {
          paintTile(painter, r, c, slice[c][r]);
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

void worldSpace::teleportal(int dir)
{
  //std::cout << "Using a portal!" << std::endl;
  //0 moves you down a level, 1 moves you up a level.
  if(dir == 0)
    {
      if(clvl == lvl1)
        {
          clvl = lvl2;
          onlvl = 2;
        }
      else if(clvl == lvl2)
        {
          clvl = lvl3;
          onlvl = 3;
        }
    }
  else if(dir == 1)
    {
      if(clvl == lvl3)
        {
          clvl = lvl2;
          onlvl = 2;
        }
      else if(clvl == lvl2)
        {
          clvl = lvl1;
          onlvl = 1;
        }
    }

  updateSlice();
  update();
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

//Put in for debugging reasons.
void worldSpace::printLevel(int alvl)
{
  if(alvl == 0)
    {
      for(int c = 0; c < COL; c++)
        {
          for(int r = 0; r < ROW; r++)
            {
              std::cout << rockmap[c][r];
            }
          std::cout << std::endl;
        } 
    }
  else if(alvl == 1)
    {
      for(int c = 0; c < COL; c++)
        {
          for(int r = 0; r < ROW; r++)
            {
              std::cout << lvl1[c][r];
            }
          std::cout << std::endl;
        } 
    }
  else if(alvl == 2)
    {
      for(int c = 0; c < COL; c++)
        {
          for(int r = 0; r < ROW; r++)
            {
              std::cout << lvl2[c][r];
            }
          std::cout << std::endl;
        }
    }
  else if(alvl == 3)
    {
      for(int c = 0; c < COL; c++)
        {
          for(int r = 0; r < ROW; r++)
            {
              std::cout << lvl3[c][r];
            }
          std::cout << std::endl;
        }
    }
}

QRect worldSpace::currentTile(int grow, int gcol)
{
  return QRect(grow * TILESIZE, gcol * TILESIZE, 
               TILESIZE, TILESIZE);
}
