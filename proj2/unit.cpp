#include "unit.h"

//Constructors
unit::unit()
{
  cXpos = 0;
  cYpos = 0;
  mSpeed = 3;
  selected = false;
}

unit::unit(int fXpos, int fYpos, int fMspeed)
{
  cXpos = fXpos;
  cYpos = fYpos;
  mSpeed = fMspeed;
  selected = false;
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
