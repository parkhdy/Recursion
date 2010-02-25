#include <QPainter>
#include <QMouseEvent>
#include <iostream>

#include "worldspace.h"

worldSpace::worldSpace(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(0, 0, 0)));
  setAutoFillBackground(true);
  cXpos = 4;
  cYpos = 5;
  onlvl = 1;
  
  //Initalizes the "permanent" vectors to the correct size.
  rockmap = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL,tile(0,0,'n')));
  slice = std::vector<std::vector<tile> > (WINSIZE, 
                                           std::vector<tile>(WINSIZE,tile(0,0,'n')));
  pUnits = std::vector<unit> (1, unit(2,3));

  //Initalizes the "impermanent" vectors to the correct size.
  lvl1 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'g')));
  lvl2 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'n')));
  lvl3 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'g')));

  //Initalize the down portal, the up portal and some terrain features.
  //The fact that these are held in text files make for easy editing by me!
  //Thank god for small favors amirite?
  rockmap = cartographer.readLevel(0);
  lvl1 = cartographer.readLevel(1);
  lvl2 = cartographer.readLevel(2);

  //Initalize the up/down portal for level 3
  lvl3[18][20].setType('u');
 

  //The default clvl, or current level, is level 1.
  clvl = lvl1;

  updateSlice();
  update();
}

/*************************************
 *SLOTS
 *************************************/

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
          if(clvl[c][r].getType() == 'w' && rockmap[c][r].getType() == 'r')
            {
              if(onlvl == 1)
                {
                  lvl1[c][r].setType('g');
                  clvl = lvl1;
                }
              else if(onlvl == 2)
                {
                  lvl2[c][r].setType('g');
                  clvl = lvl2;
                }
              else if(onlvl == 3)
                {
                  lvl3[c][r].setType('g');
                  clvl = lvl3;
                }

              rockmap[c][r].setType('n');
            }
        }
    }

  //Update Slice with the current terrain. The -12 slapped on cXpos makes
  //sure that slice is centered around the camera.
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
            {
              //std::cout << "Updated Slice: x: " << c2 << ", y: " << r2 << std::endl;
              //std::cout << "With tile: x: " << c << ", y: " << r << std::endl;
              //std::cout << "Tile has xid: " << clvl[c][r].getX() << ", y: " << clvl[c][r].getY() << std::endl;
              slice[c2][r2].setType(clvl[c][r].getType());
              slice[c2][r2].setX(clvl[c][r].getX());
              slice[c2][r2].setY(clvl[c][r].getY());
            }
          else
            {
              slice[c2][r2].setType('n');
              slice[c2][r2].setX(-1);
              slice[c2][r2].setY(-1);
            }
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
             && (rockmap[c][r].getType() == 'r'))
            slice[c2][r2].setType(rockmap[c][r].getType());
          r2 = r2 + 1;
        }
      c2 = c2 + 1;
    }
  
  emit sendMap(prepMap());
}

/*************************************
 *PROTECTED
 *************************************/

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

//This is supposed to tell you what tile you're clicking on when you click on the screen
//Unfortunatley, it's incredibly inaccurate so far. This definitely needs some fine tuning.
void worldSpace::mousePressEvent(QMouseEvent *event)
{
  if (event->button() != Qt::LeftButton)
    return;
  else
    {
      QPoint pos = event->pos();

      int sliceX = pos.x();
      int sliceY = pos.y();

      int slXrel = pos.y() / 20;
      int slYrel = pos.x() / 20;

      int tileX = slice[slXrel][slYrel].getX();
      int tileY = slice[slXrel][slYrel].getY();

      if(slice[slXrel][slYrel].getX() < 0 || slice[slXrel][slYrel].getY() < 0)
        {
          tileX = 0;
          tileY = 0;
          std::cout << "Picked an invalid tile. This is here to prevent a seg fault." << std::endl;
        }

      std::cout << "Clicked Worldspace at: x: " << sliceX << ", y: " << sliceY << std::endl;

      std::cout << "Estimated slice position: x: " << slXrel 
                << ", y: " << slYrel << std::endl;

      std::cout << "Slice position relative to tile postion: x: " << slice[slXrel][slYrel].getX()
                << ", y: " << slice[slXrel][slYrel].getY() << std::endl;

      std::cout << "Actual tile picked: x: " << clvl[tileX][tileY].getX()
                << ", y: " << clvl[tileX][tileY].getY() << std::endl << std::endl;

      for(size_t x = 0; x < pUnits.size(); x++)
        {
          if(isUnit(x, clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()))
            std::cout << "There is a unit here!" << std::endl;
        }
    }
  
  //printLevel(4);
}

/*************************************
 *PRIVATE
 *************************************/

//Prepares a map to send.
std::vector<std::vector<tile> > worldSpace::prepMap()
{
  std::vector<std::vector<tile> > preppedMap;
  preppedMap = clvl;
  //Updates a new array representing the map with the rockmap for reference. 
  //Should also probably show where the player is. I can easily add this.
  for(int c = 0; c < COL; c++)
    {
      for (int r = 0; r < ROW; r++)
        {
          if(rockmap[c][r].getType() == 'r')
            preppedMap[c][r].setType('r');
          if(c == cXpos && r == cYpos)
            preppedMap[c][r].setType('p');
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
  return clvl[cXpos][cYpos].getType();
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

  //std::cout << "Moved to: " << lvl1[cXpos][cYpos].getX() << ", " << lvl1[cXpos][cYpos].getY() << std::endl;
  //std::cout << "Current Xpos: " << cXpos << ", Current Ypos: " << cYpos << std::endl;
  update();
  emit moved();
}

bool worldSpace::canPush(int dir)
{
  if(dir == 0)
    {
      if (cYpos-2 >= 0
          && clvl[cXpos][cYpos-1].getType() != 'i' && clvl[cXpos][cYpos-1].getType() != 'w'
          && clvl[cXpos][cYpos-2].getType() != 'i' 
          && rockmap[cXpos][cYpos-2].getType() == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 1)
    {
      if (cYpos+2 < COL
          && clvl[cXpos][cYpos+1].getType() != 'i' && clvl[cXpos][cYpos+1].getType() != 'w'
          && clvl[cXpos][cYpos+2].getType() != 'i'
          && rockmap[cXpos][cYpos+2].getType() == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 2)
    {
      if (cXpos+2 < ROW
          && clvl[cXpos+1][cYpos].getType() != 'i' && clvl[cXpos+1][cYpos].getType() != 'w'
          && clvl[cXpos+2][cYpos].getType() != 'i' 
          && rockmap[cXpos+2][cYpos].getType() == 'n')
        return true;
      else
        return false;
    }
  else //Dir == 3
    {
      if (cXpos-2 >= 0
          && clvl[cXpos-1][cYpos].getType() != 'i' && clvl[cXpos-1][cYpos].getType() != 'w'
          && clvl[cXpos-2][cYpos].getType() != 'i'
          && rockmap[cXpos-2][cYpos].getType() == 'n')
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
      if(/*clvl == lvl1*/onlvl == 1)
        {
          clvl = lvl2;
          onlvl = 2;
        }
      else if(/*clvl == lvl2*/onlvl == 2)
        {
          clvl = lvl3;
          onlvl = 3;
        }
    }
  else if(dir == 1)
    {
      if(/*clvl == lvl3*/onlvl == 3)
        {
          clvl = lvl2;
          onlvl = 2;
        }
      else if(/*clvl == lvl2*/onlvl == 2)
        {
          clvl = lvl1;
          onlvl = 1;
        }
    }

  updateSlice();
  update();
  emit updateTree(onlvl);
}

void worldSpace::push(int dir)
{
  //Push a rock north
  if(dir == 0)
    {
      rockmap[cXpos][cYpos-1].setType('n');
      rockmap[cXpos][cYpos-2].setType('r');
    }
  //Push a rock south
  else if(dir == 1)
    {
      rockmap[cXpos][cYpos+1].setType('n');
      rockmap[cXpos][cYpos+2].setType('r');
    }
  //Push a rock east / right
  else if(dir == 2)
    {      
      rockmap[cXpos+1][cYpos].setType('n');
      rockmap[cXpos+2][cYpos].setType('r');      
    }
  //Push a rock west / left
  else //Dir == 3
    {     
      rockmap[cXpos-1][cYpos].setType('n');
      rockmap[cXpos-2][cYpos].setType('r');
    }
}

//Very simple tool for finding out whether a unit is in
//a certain position or not.
//Preconditions = given a slot, x position and y position
//Postconditions = Returns true if the unit in (xloc, yloc)
// is the one specified in the slot. False otherwise.
bool worldSpace::isUnit(int slot, int xloc, int yloc)
{
  if(pUnits[slot].getX() == xloc &&
     pUnits[slot].getY() == yloc)
    return true;
  else
    return false;
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
      if( clvl[cXpos][cYpos-1].getType() != 'i' 
          && clvl[cXpos][cYpos-1].getType() != 'w'
          && rockmap[cXpos][cYpos-1].getType() == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 1)
    {
      if( clvl[cXpos][cYpos+1].getType() != 'i' 
          && clvl[cXpos][cYpos+1].getType() != 'w'
          && rockmap[cXpos][cYpos+1].getType() == 'n')
        return true;
      else
        return false;
    }
  else if(dir == 2)
    {
     if( clvl[cXpos+1][cYpos].getType() != 'i' 
         && clvl[cXpos+1][cYpos].getType() != 'w'
         && rockmap[cXpos+1][cYpos].getType() == 'n')
        return true;
      else
        return false;
    }
  else //Dir == 3
    {
      if( clvl[cXpos-1][cYpos].getType() != 'i'
          && clvl[cXpos-1][cYpos].getType() != 'w'
          && rockmap[cXpos-1][cYpos].getType() == 'n')
        return true;
      else
        return false; 
    }
}

void worldSpace::paintTile(QPainter &painter, 
                           int row, int col, 
                           tile til)
{
  painter.setPen(Qt::NoPen);

  if(til.getType() == 'g')
    painter.setBrush(Qt::green);
  else if(til.getType() == 'r')
    painter.setBrush(Qt::gray);
  else if(til.getType() == 'n')
    painter.setBrush(Qt::black);
  else if(til.getType() == 'd')
    painter.setBrush(QColor(250, 25, 150));
  else if(til.getType() == 'u')
    painter.setBrush(QColor(250, 150, 25));
  else if(til.getType() == 'i')
    painter.setBrush(QColor(0, 125, 0));
  else if(til.getType() == 'w')
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
              std::cout << rockmap[c][r].getType();
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
              std::cout << lvl1[c][r].getType();
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
              std::cout << lvl2[c][r].getType();
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
              std::cout << lvl3[c][r].getType();
            }
          std::cout << std::endl;
        }
    }
  else if(alvl == 4)
    {
      for(int c = 0; c < WINSIZE; c++)
        {
          for(int r = 0; r < WINSIZE; r++)
            {
              std::cout << "[" << slice[c][r].getType() << "," 
                        << slice[c][r].getX() << ","
                        << slice[c][r].getY() << "]";
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
