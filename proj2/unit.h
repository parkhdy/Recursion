#ifndef UNIT_H
#define UNIT_H

class unit
{
public:
  //Constructors
  unit();
  unit(int fXpos, int fYpos);

  //Selectors
  int getX();
  int getY();

  //Mutators
  void sel();
  void desel();

private:
  //Member variables
  int cXpos;
  int cYpos;
  bool selected;
};

#endif
