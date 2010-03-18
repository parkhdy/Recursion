#include "unit.h"

//Constructors
unit::unit()
{
  cXpos = 0;
  cYpos = 0;
  mSpeed = 3;
  selected = false;
}

unit::unit(int fXpos, int fYpos, int fMspeed,
           std::string fName, std::string fTitle, int fHP)
{
  cXpos = fXpos;
  cYpos = fYpos;
  mSpeed = fMspeed;
  selected = false;

  unitName = fName;
  unitTitle = fTitle;
  mHP = fHP;
  cHP = mHP;
}

//Selectors
int unit::getX()
{
  return cXpos;
}

int unit::getY()
{
  return cYpos;
}

int unit::getSpeed()
{
  return mSpeed;
}

bool unit::isSelected()
{
  return selected;
}

std::string unit::getName()
{
  return unitName;
}

std::string unit::getTitle()
{
  return unitTitle;
}
  
int unit::getmHP()
{
  return mHP;
}
  
int unit::getcHP()
{
  return cHP;
}

//Mutators
void unit::move(int nextX, int nextY)
{
  cXpos = nextX;
  cYpos = nextY;
}

void unit::sel()
{
  selected = true;
}

void unit::desel()
{
  selected = false;
}
