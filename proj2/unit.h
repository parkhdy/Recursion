#ifndef UNIT_H
#define UNIT_H

class unit
{
public:
  //Constructors
  unit();
  unit(int fXpos, int fYpos, int fSpeed);

  //Selectors
  int getX();
  int getY();
  int getSpeed();
  bool isSelected();

  //Mutators
  void move(int nextX, int nextY);
  void sel();
  void desel();

private:
  //Member variables
  int cXpos;
  int cYpos;
  int mSpeed;
  bool selected;
};

#endif
