#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "defs.h"

class mapMaker
{

public:
  mapMaker();
  std::vector<std::vector<char> > readLevel(int whichlevel);
  void printLevel(std::vector<std::vector<char> > clvl);
  
private:
  std::ifstream infile;
};

#endif
