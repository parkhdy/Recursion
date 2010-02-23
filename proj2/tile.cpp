#include "tile.h"

tile::tile()
{
  Xid = 0;
  Yid = 0;
}

tile::tile(int gxid, int gyid, char gtype)
{
  Xid = gxid;
  Yid = gyid;
  tiletype = gtype;
}

int tile::getX()
{
  return Xid;
}

int tile::getY()
{
  return Yid;
}

char tile::getType()
{
  return tiletype;
}

void tile::setType(char nextType)
{
  tiletype = nextType;
}

void tile::setX(int nextX)
{
  Xid = nextX;
}

void tile::setY(int nextY)
{
  Yid = nextY;
}

bool tile::operator== (const tile& t1) const
{
  /*
  if(tiletype == t1.getType() &&
     Xid == t1.getX() &&
     Yid == t1.getY())
    return true;
  else
    return false;
  */
}
