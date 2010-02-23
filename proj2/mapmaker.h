#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "defs.h"
#include "tile.h"

class mapMaker
{

public:
  mapMaker();
  std::vector<std::vector<tile> > readLevel(int whichlevel);
  void printLevel(std::vector<std::vector<tile> > clvl);
  
private:
  std::ifstream infile;
};

#endif
