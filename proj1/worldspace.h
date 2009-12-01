#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <vector>

#include "defs.h"

class worldSpace : public QWidget
{
  Q_OBJECT

  public:
  worldSpace(QWidget *parent = 0);

public slots:
  void moveUP();
  void moveDOWN();
  void moveLEFT();
  void moveRIGHT();
  void updateSlice();

signals:
  void moved();
  void updateMap();
  std::vector<std::vector<char> > sendMap(std::vector<std::vector<char> > newmap);

protected:
  void paintEvent(QPaintEvent *event);

private:
  std::vector<std::vector<char> > prepMap();
  void moveChar(int dir);
  bool traversable(int dir);
  bool canPush(int dir);
  void push(int dir);
  void paintTile(QPainter &painter, 
                 int row, int col,
                 char type);

  int cXpos;
  int cYpos;
  int cdir; //0 = Up, 1 = Down, 2 = Right, 3 = Left

  QRect currentTile(int grow, int gcol);

  //The 3 'permanent' vectors that are visible no matter what.
  std::vector<std::vector<char> > slice;
  std::vector<std::vector<char> > rockmap;
  std::vector<std::vector<char> > clvl;

  //The 'impermanent' vectors that are not always visible.
  std::vector<std::vector<char> > lvl1;
};

#endif
