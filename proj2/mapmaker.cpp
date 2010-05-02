#include "mapmaker.h"

mapMaker::mapMaker()
{
}

std::vector<std::vector<tile> > mapMaker::readLevel(int whichlevel)
{
  if(whichlevel == 0)
    infile.open("overlay.txt");
  if(whichlevel == 1)
    infile.open("level0.txt");
  if(whichlevel == 2)
    infile.open("level1.txt");
  if(whichlevel == 3)
    infile.open("level2.txt");

  std::vector<std::vector<tile> > amap;
  amap = std::vector<std::vector<tile> > (30, std::vector<tile>(30,tile()));

  char nextlet;

  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW+1; r++)
        {
          infile.get(nextlet);
          if(nextlet != '\n')
            amap[c][r] = tile(c,r,nextlet);
        }
    }
  
  infile.close();
  return amap;                               
}

void mapMaker::printLevel(std::vector<std::vector<tile> > clvl)
{
  //cout << clvl.size() << endl;
  for(int r = 0; r < ROW+1; r++)
    {
      //cout << "Printing from row: " << r << "Size: " << clvl[r].size() << endl;
      for(int c = 0; c < COL+1; c++)
        {          
          std::cout << clvl[r][c].getType();
        }
      //cout << "Printing a newline!" << endl;
      std::cout << std::endl;
    } 
}
