#include "defs.h"
#include "gamespace.h"

//Constructor for the gamespace class
gameSpace::gameSpace(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *button1 = new QPushButton(tr("Orders"));
  button1->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button2 = new QPushButton(tr("End Turn"));
  button2->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button3 = new QPushButton(tr("Quests"));
  button3->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button4 = new QPushButton(tr("Log"));
  button4->setFont(QFont("Times", 18, QFont::Bold));

  wspace = new worldSpace;
  
  wtree = new worldTree;
  
  lmap = new localMap;

  (void) new QShortcut(Qt::Key_Up, wspace, SLOT(moveUP()));
  (void) new QShortcut(Qt::Key_Right, wspace, SLOT(moveRIGHT()));
  (void) new QShortcut(Qt::Key_Down, wspace, SLOT(moveDOWN()));
  (void) new QShortcut(Qt::Key_Left, wspace, SLOT(moveLEFT()));
  (void) new QShortcut(Qt::CTRL + Qt::Key_Q, this, SLOT(close()));

  connect(button1, SIGNAL(clicked()), 
          this, SLOT(showOrderWindow()));

  connect(button2, SIGNAL(clicked()),
          wspace, SLOT(endYourTurn()));

  connect(this, SIGNAL(pickedUnitm(unit)),
          wspace, SLOT(movementOverlay(unit)));

  connect(this, SIGNAL(pickedUnita(unit)),
          wspace, SLOT(attackOverlay(unit)));

  connect(wspace, SIGNAL(deselectall()),
          wspace, SLOT(wipeOverlay()));

  connect(wspace, SIGNAL(moved()), 
          wspace, SLOT(updateSlice()));

  connect(wspace, SIGNAL(sendMap(std::vector<std::vector<tile> >)),
          lmap, SLOT(updateMap(std::vector<std::vector<tile> >)));

  connect(wspace, SIGNAL(updateTree(unit)),
          wtree, SLOT(updateTree(unit)));
  
  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(wspace, 0, 0, 2, 2);
  gridLayout->addWidget(wtree, 0, 2, 1, 2);
  gridLayout->addWidget(lmap, 1, 2, 1, 2);
  gridLayout->addWidget(button1, 2, 0);
  gridLayout->addWidget(button2, 2, 1);
  gridLayout->addWidget(button3, 2, 2);
  gridLayout->addWidget(button4, 2, 3);
  gridLayout->setColumnStretch(0, 8);
  gridLayout->setColumnStretch(1, 8);
  setLayout(gridLayout);
}

void gameSpace::startTutorial()
{
  wspace->loadlevel(1);
}

void gameSpace::moveOrderSent()
{
  //std::cout << "Going into moverordersent" << std::endl;
  emit pickedUnitm(wspace->selectedUnitsel());
}

void gameSpace::attackOrderSent()
{
  emit pickedUnita(wspace->selectedUnitsel());
}

void gameSpace::showOrderWindow()
{
  if(wspace->isUnitSelected())
    emit showCharwin();
}
