#include "unit.h"

//Constructors
unit::unit()
{
  cXpos = 0;
  cYpos = 0;
  selected = false;
}

unit::unit(int fXpos, int fYpos)
{
  cXpos = fXpos;
  cYpos = fYpos;
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

//Mutators
void unit::sel()
{
  selected = true;
}

void unit::desel()
{
  selected = false;
}
