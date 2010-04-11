#ifndef GAMESPACE_H
#define GAMESPACE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>
#include <QLabel>

#include "gamespace.h"
#include "worldspace.h"
#include "worldtree.h"
#include "localmap.h"
#include "tile.h"

//The gamespace class, which inherits from QWidget
class gameSpace : public QWidget
{
  Q_OBJECT

public:
  gameSpace(QWidget *parent = 0);

signals:
  void showCharwin();
  void pickedUnitm(unit);
  void pickedUnita(unit);

public slots:
  void moveOrderSent();
  void attackOrderSent();
  void showOrderWindow();

private:
  worldSpace *wspace;
  worldTree *wtree;
  localMap *lmap;
};

#endif
