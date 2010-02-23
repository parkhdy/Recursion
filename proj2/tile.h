#ifndef TILE_H
#define TILE_H

#include "defs.h"

class tile
{
public:
  //Constructors
  tile();
  tile(int gxid, int gyid, char gtype);

  //Access methods
  int getX();
  int getY();
  char getType();
  
  //Mutators
  void setType(char nextType);
  void setX(int nextX);
  void setY(int nextY);

  //Operators?
  bool operator== (const tile& t1) const;

private:
  int Xid;
  int Yid;
  char tiletype;
};

#endif
