#include "mapmaker.h"

mapMaker::mapMaker()
{
}

std::vector<std::vector<char> > mapMaker::readLevel(int whichlevel)
{
  if(whichlevel == 0)
    infile.open("rawkmap.txt");
  if(whichlevel == 1)
    infile.open("level1.txt");

  std::vector<std::vector<char> > amap;
  amap = std::vector<std::vector<char> > (30, std::vector<char>(30,'n'));

  char nextlet;

  for(int c = 0; c < COL; c++)
    {
      for(int r = 0; r < ROW+1; r++)
        {
          infile.get(nextlet);
          if(nextlet != '\n')
            amap[c][r] = nextlet;
        }
    }
  
  infile.close();
  return amap;                               
}

void mapMaker::printLevel(std::vector<std::vector<char> > clvl)
{
  //cout << clvl.size() << endl;
  for(int r = 0; r < ROW+1; r++)
    {
      //cout << "Printing from row: " << r << "Size: " << clvl[r].size() << endl;
      for(int c = 0; c < COL+1; c++)
        {          
          std::cout << clvl[r][c];
        }
      //cout << "Printing a newline!" << endl;
      std::cout << std::endl;
    } 
}
