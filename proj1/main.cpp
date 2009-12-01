#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>
#include <vector>

#include "worldspace.h"
#include "worldtree.h"
#include "localmap.h"

class gameSpace : public QWidget
{
  //Q_OBJECT

public:
  gameSpace(QWidget *parent = 0);

public slots:
  void charWindow();
};

class subWindow : public QWidget
{
public:
  subWindow(QWidget *parent);
};

subWindow::subWindow(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *button1 = new QPushButton(tr("Button"));
  
  QGridLayout *gridLayout = new QGridLayout;
  gridLayout->addWidget(button1, 0, 0);
  setLayout(gridLayout);
}

gameSpace::gameSpace(QWidget *parent)
  : QWidget(parent)
{
  QPushButton *button1 = new QPushButton(tr("Button"));
  button1->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button2 = new QPushButton(tr("Button"));
  button2->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button3 = new QPushButton(tr("Button"));
  button3->setFont(QFont("Times", 18, QFont::Bold));

  QPushButton *button4 = new QPushButton(tr("Button"));
  button4->setFont(QFont("Times", 18, QFont::Bold));

  worldSpace *wspace = new worldSpace;

  worldTree *wtree = new worldTree;

  localMap *lmap = new localMap;

  (void) new QShortcut(Qt::Key_Up, wspace, SLOT(moveUP()));
  (void) new QShortcut(Qt::Key_Right, wspace, SLOT(moveRIGHT()));
  (void) new QShortcut(Qt::Key_Down, wspace, SLOT(moveDOWN()));
  (void) new QShortcut(Qt::Key_Left, wspace, SLOT(moveLEFT()));
  (void) new QShortcut(Qt::CTRL + Qt::Key_Q, this, SLOT(close()));

  connect(button1, SIGNAL(clicked()), 
          this, SLOT(charWindow()));

  connect(wspace, SIGNAL(moved()), 
          wspace, SLOT(updateSlice()));

  connect(wspace, SIGNAL(sendMap(std::vector<std::vector<char> >)),
          lmap, SLOT(updateMap(std::vector<std::vector<char> >)));
                         
          
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

void gameSpace::charWindow()
{
  subWindow subwin(this);
  subwin.show();
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  gameSpace warudo;
  warudo.setGeometry(100, 100, 700, 575);
  warudo.show();
  return app.exec();
}
