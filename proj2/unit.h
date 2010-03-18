#ifndef UNIT_H
#define UNIT_H

#include <string>

class unit
{
public:
  //Constructors
  unit();
  unit(int fXpos, int fYpos, int fSpeed,
       std::string fName, std::string fTitle, int fHP);

  //Selectors
  int getX();
  int getY();
  int getSpeed();
  bool isSelected();

  std::string getName();
  std::string getTitle();
  int getmHP();
  int getcHP();

  //Mutators
  void move(int nextX, int nextY);
  void sel();
  void desel();

private:
  //Member variables - "hard data"
  int cXpos;
  int cYpos;
  int mSpeed;
  bool selected;

  //Information pertaining - "soft data"
  std::string unitName;
  std::string unitTitle;
  int cHP;
  int mHP;
};

#endif
