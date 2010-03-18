#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <vector>

#include "defs.h"
#include "tile.h"
#include "unit.h"
#include "mapmaker.h"

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
  void movementOverlay(unit uni);
  void wipeOverlay();

signals:
  void moved();
  void updateMap();
  std::vector<std::vector<tile> > sendMap(std::vector<std::vector<tile> > newmap);
  void updateTree(unit uni);
  unit selectedUnit(unit uni);
  void deselectall();

protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:
  std::vector<std::vector<tile> > prepMap();
  unit pickUnit(int xPos, int yPos);
  char onPortal();
  void moveChar(int dir);
  bool isUnit(int slot, int xloc, int yloc);
  void paintTile(QPainter &painter, 
                 int row, int col,
                 tile til);

  void printLevel(int alvl);

  int cXpos;
  int cYpos;
  int cdir; //0 = Up, 1 = Down, 2 = Right, 3 = Left
  int onlvl;
  mapMaker cartographer;

  QRect currentTile(int grow, int gcol);

  //Contains all of the player's units
  std::vector<unit> pUnits;

  //The 3 'permanent' vectors that are visible no matter what.
  std::vector<std::vector<tile> > slice;
  std::vector<std::vector<tile> > overlay;
  std::vector<std::vector<tile> > clvl;

  //The 'impermanent' vectors that are not always visible.
  std::vector<std::vector<tile> > lvl1;
  std::vector<std::vector<tile> > lvl2;
  std::vector<std::vector<tile> > lvl3;
};

#endif
