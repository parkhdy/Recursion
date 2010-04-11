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
  playerTurn = true;
  
  //Initalizes the "permanent" vectors to the correct size.
  overlay = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL,tile(0,0,'n')));
  slice = std::vector<std::vector<tile> > (WINSIZE, 
                                           std::vector<tile>(WINSIZE,tile(0,0,'n')));
  //Add some units
  pUnits = std::vector<unit> (1, unit(2,3,4,
                                      "Sahar", "Demon Queen", 100));
  pUnits.push_back(unit(5,6,4,
                        "Lyri", "San'layn Initiate", 100));


  //Add some enemies
  eUnits = std::vector<unit> (1, unit(12,15,4,
                                      "Jim", "Soldier", 11));
  eUnits.push_back(unit(10,18,4,
                        "John", "Soldier", 11));

  //Initalizes the "impermanent" vectors to the correct size.
  lvl1 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'g')));
  lvl2 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'n')));
  lvl3 = std::vector<std::vector<tile> > (ROW, std::vector<tile>(COL, tile(0,0,'g')));

  //Initalize the down portal, the up portal and some terrain features.
  //The fact that these are held in text files make for easy editing by me!
  //Thank god for small favors amirite?
  overlay = cartographer.readLevel(0);
  lvl1 = cartographer.readLevel(1);
  lvl2 = cartographer.readLevel(2);

  //The default clvl, or current level, is level 1.
  clvl = lvl1;

  updateSlice();
  update();
}

/*************************************
 *SELECTORS
 *************************************/

unit worldSpace::selectedUnitsel()
{
  for(size_t x = 0; x < pUnits.size(); x++)
    {
      if(pUnits[x].isSelected())
        return pUnits[x];
    }
}

bool worldSpace::isUnitSelected()
{
  bool unitSelected = false;
  
  for(size_t x = 0; x < pUnits.size(); x++)
    if(pUnits[x].isSelected())
      {
        unitSelected = true;
      }

  return unitSelected;
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

  //Update Slice with the Overlay
  c2 = 0;
  for(int c = cXpos-12; c < cXpos+13; c++)
    {
      int r2 = 0;
      for(int r = cYpos-12; r < cYpos+13; r++)
        {
          if((r >= 0 && r < ROW) && (c >= 0 && c < COL) 
             && ((overlay[c][r].getType() == 'v') 
                 || (overlay[c][r].getType() == 'a')))
            slice[c2][r2].setType(overlay[c][r].getType());
          r2 = r2 + 1;
        }
      c2 = c2 + 1;
    }

  emit sendMap(prepMap());
}

//Sets up an overlay that shows valid movement spots for units.
//Need to figure out how to give this an alpha value sometime.
void worldSpace::movementOverlay(unit uni)
{ 
  int xCost = 0;
  int yCost = 0;
  int tCost = 0;

  //Looks at every single tile on the overlay.
  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {          
          if(uni.getY() > c)
            yCost = uni.getY() - c;
          else
            yCost = c - uni.getY();

          if(uni.getX() > r)
            xCost = uni.getX() - r;
          else
            xCost = r - uni.getX();

          tCost = xCost + yCost;

          if(tCost <= uni.getSpeed())
            overlay[r][c].setType('v');
          else
            overlay[r][c].setType('n');
        }
    }
  
  emit moved();
}

//This sets up an attack overlay that shows valid spaces
//for the unit to attack.
void worldSpace::attackOverlay(unit uni)
{ 
  int xCost = 0;
  int yCost = 0;
  int tCost = 0;

  //Looks at every single tile on the overlay.
  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {          
          if(uni.getY() > c)
            yCost = uni.getY() - c;
          else
            yCost = c - uni.getY();

          if(uni.getX() > r)
            xCost = uni.getX() - r;
          else
            xCost = r - uni.getX();

          tCost = xCost + yCost;

          if(tCost <= 1)
            overlay[r][c].setType('a');
          else
            overlay[r][c].setType('n');
        }
    }
  
  emit moved();
}

void worldSpace::wipeOverlay()
{
  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW; r++)
        {
          overlay[c][r].setType('n');
        }
    }

  emit moved();
}

void worldSpace::endYourTurn()
{
  playerTurn = false;
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
  //The "player" is becoming the "camera" and is no longer drawn.
  painter.setPen(Qt::NoPen);
  /*
  painter.setBrush(Qt::red);
  
  painter.drawRect(QRect(12*TILESIZE, 12*TILESIZE,
                         TILESIZE, TILESIZE));
  */
}

//This is supposed to tell you what tile you're clicking on when you click on the screen
//I fixed it. The problem was with the fact that it wasn't swapping x/y values properly.
void worldSpace::mousePressEvent(QMouseEvent *event)
{
  if (event->button() != Qt::LeftButton)
    {
      //Deslects all units.
      for(size_t x = 0; x < pUnits.size(); x++)
        {
          pUnits[x].desel();
        }
      emit deselectall();
    }
  else if (event->button() == Qt::LeftButton && playerTurn)
    {
      QPoint pos = event->pos();

      //int sliceX = pos.x();
      //int sliceY = pos.y();

      int slXrel = pos.y() / 20;
      int slYrel = pos.x() / 20;

      if(slXrel > 24)
        slXrel = 24;
      if(slYrel > 24)
        slYrel = 24;

      int tileX = slice[slXrel][slYrel].getX();
      int tileY = slice[slXrel][slYrel].getY();
      
      //The following are output lines for debugging purposes.

      /*
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
      */

      bool unitPresent = false;
      bool enemyPresent = false;
      int enemyslot;

      //This will detect any unit that is clicked on.
      //If an enemy unit is clicked on, this will save the slot of it, for later reference
      for(size_t x = 0; x < pUnits.size(); x++)
        {
          if(tileX >= 0 && tileY >= 0)
            if(isUnit(x, clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()))
              unitPresent = true;
        }

      for(size_t x = 0; x < eUnits.size(); x++)
        {
          if(tileX >= 0 && tileY >= 0)
            if(isEnem(x, clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()))
              {
                enemyslot = x;
                enemyPresent = true;
              }
        }

      //and will deselect the unit only if another one is left clicked on
      if(unitPresent)
        {
          for(size_t x = 0; x < pUnits.size(); x++)
            {
              if(isUnit(x, clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()))
                {
                  //std::cout << "There is a unit here!" << std::endl;
                  pUnits[x].sel();
                  //emit selectedUnit(pickUnit(clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()));
                  emit updateTree(pickUnit(clvl[tileX][tileY].getX(), clvl[tileX][tileY].getY()));
                }
              else
                pUnits[x].desel();
            }
        }
      else
        {
          //If the clicking function goes into here, it means that a unit has NOT been clicked on. First check
          //to see if there is a unit selected.
          bool unitSelected = false;
          int unitSlot = 0;

          for(size_t x = 0; x < pUnits.size(); x++)
            if(pUnits[x].isSelected())
              {
                unitSelected = true;
                unitSlot = x;
              }

          //If a unit is selected, check the overlay to see if you want to move it to a valid spot. If so, move it.
          //If this is not the case, check the overlay to see if you want it to ATTACK a valid spot. If so, attack.
          if(unitSelected)
            {
              //The next X position to move the unit to.
              if(tileX >= 0 && tileY >= 0)
                {
                  int nextX = overlay[tileX][tileY].getX();
                  int nextY = overlay[tileX][tileY].getY();

                  bool enemyUnit = false;

                  for(size_t x = 0; x < eUnits.size(); x++)
                    {
                      if(isEnem(x,nextX,nextY))
                        enemyUnit = true;
                    }

                  if(overlay[tileX][tileY].getType() == 'v' && !enemyUnit)
                    {
                      pUnits[unitSlot].move(nextX, nextY);
                      pUnits[unitSlot].desel();
                    }
                  else if(overlay[tileX][tileY].getType() == 'a')
                    {
                      if(enemyPresent)
                        {
                          int attackDamage = pUnits[unitSlot].atkDMG();
                          eUnits[enemyslot].takeDamage(attackDamage);
                          std::cout << "Enemy has " << eUnits[enemyslot].getcHP() << " more HP." << std::endl;
                          pUnits[unitSlot].desel();

                          for(size_t x = 0; x < eUnits.size(); x++)
                            {
                              if(eUnits[x].getcHP() <= 0)
                                eUnits.erase(eUnits.begin()+x);
                            }
                        }
                    }
                  emit deselectall();
                  emit moved();
                }
            }
        }
    }

   
  //printLevel(4);
  update();
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
          for(size_t x = 0; x < pUnits.size(); x++)
            {
              if(isUnit(x,c,r))
                preppedMap[c][r].setType('t');
            }          
        }
    }

  return preppedMap;
}

unit worldSpace::pickUnit(int xPos, int yPos)
{
  emit deselectall();
  for(size_t x = 0; x < pUnits.size(); x++)
    {
      if(isUnit(x,xPos,yPos))
        return pUnits[x];
    }
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
      else
        cYpos -= 1;
    }
  //Move right / east
  else if(dir == 1)
    {
      if(cYpos >= COL-1)
        return;
      else
        cYpos += 1;
    }
  //Move down / south
  else if(dir == 2)
    {
      if(cXpos >= ROW-1)
        return;
      else
        cXpos += 1;
    }
  //move up / north
  else if(dir == 3)
    {
      if(cXpos == 0)
        return;
      else
        cXpos -= 1;
    }

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

bool worldSpace::isEnem(int slot, int xloc, int yloc)
{
  if(eUnits[slot].getX() == xloc &&
     eUnits[slot].getY() == yloc)
    return true;
  else
    return false;
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
  else if(til.getType() == 'v')
    painter.setBrush(QColor(100,100,200));
  else if(til.getType() == 'a')
    painter.setBrush(QColor(200,100,100));
  for(size_t x = 0; x < pUnits.size(); x++)
    {
      if(isUnit(x, til.getX(), til.getY()))
        painter.setBrush(QColor(100,200,100));
      if(isUnit(x, til.getX(), til.getY()) && 
         pUnits[x].isSelected())
        painter.setBrush(QColor(80,255,80));
      if(isEnem(x, til.getX(), til.getY()))
        painter.setBrush(QColor(200,100,100));
    }
    
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
              std::cout << overlay[c][r].getType();
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
