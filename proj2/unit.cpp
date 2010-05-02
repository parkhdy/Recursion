#include "unit.h"

//Constructors
unit::unit()
{
  cXpos = 0;
  cYpos = 0;
  mSpeed = 3;
  selected = false;
  alive = true;

  minDMG = 5;
  maxDMG = 10;
}

unit::unit(int fXpos, int fYpos, int fMspeed,
           std::string fName, std::string fTitle, int fHP)
{
  cXpos = fXpos;
  cYpos = fYpos;
  mSpeed = fMspeed;
  selected = false;
  alive = true;

  unitName = fName;
  unitTitle = fTitle;
  mHP = fHP;
  cHP = mHP;

  minDMG = 5;
  maxDMG = 10;
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

bool unit::isLive()
{
  return alive;
}

int unit::atkDMG()
{
  int thePain;
  thePain = atkDamage.randInt(minDMG, maxDMG);

  return thePain;
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

void unit::takeDamage(int damage)
{
  cHP = cHP - damage;
}

void unit::kill()
{
  alive = false;
}
