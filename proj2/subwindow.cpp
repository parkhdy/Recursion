#include "subwindow.h"

//Constructor for the Subwindow class
actionMenu::actionMenu(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *button1 = new QPushButton(tr("Move"));
  button1->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button2 = new QPushButton(tr("Attack"));
  button2->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button3 = new QPushButton(tr("Special"));
  button3->setFont(QFont("Times", 18, QFont::Bold));
  
  QPushButton *button4 = new QPushButton(tr("Other"));
  button4->setFont(QFont("Times", 18, QFont::Bold));

  connect(button1, SIGNAL(clicked()), 
          this, SIGNAL(moveOrder()));

  connect(button2, SIGNAL(clicked()),
          this, SIGNAL(attackOrder()));

  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(button1, 0, 0);
  gridLayout->addWidget(button2, 1, 0);
  gridLayout->addWidget(button3, 2, 0);
  gridLayout->addWidget(button4, 3, 0);
  setLayout(gridLayout);
}

//Constructor for the mainMenu class
mainMenu::mainMenu(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *button1 = new QPushButton(tr("New Game"));
  button1->setFont(QFont("Times",18,QFont::Bold));

  QPushButton *button2 = new QPushButton(tr("Tutorial"));
  button2->setFont(QFont("Times",18,QFont::Bold));

  connect(button2, SIGNAL(clicked()),
          this, SIGNAL(tutStart()));

  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(button1, 0, 0);
  gridLayout->addWidget(button2, 1, 0);
  setLayout(gridLayout);
}
