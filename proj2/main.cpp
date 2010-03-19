#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>
#include <QLabel>
#include <vector>
#include <QMdiArea>
#include <QMainWindow>

#include "gamespace.h"
#include "worldspace.h"
#include "worldtree.h"
#include "localmap.h"
#include "tile.h"

class QMdiArea;

//The "mainwindow" class, which is a Qmdiarea
class mainWindow : public QMainWindow
{
  Q_OBJECT

  public:
  mainWindow();

public slots:
  void addWindow();

private:
  QMdiArea *mdiArea;
};

//A subwindow class for adding a menu
class subWindow : public QWidget
{
public:
  subWindow(QWidget *parent = 0);
};

//Constructor for the mainWindow class
mainWindow::mainWindow()
{
  mdiArea = new QMdiArea;
  setCentralWidget(mdiArea);

  gameSpace *theWorld = new gameSpace;

  connect(theWorld, SIGNAL(showCharwin()), 
         this, SLOT(addWindow()));

  mdiArea->addSubWindow(theWorld);
  theWorld->showMaximized();
}

//Slot to show the subwindow
void mainWindow::addWindow()
{
  subWindow *miscMenu = new subWindow;

  mdiArea->addSubWindow(miscMenu);
}

//Constructor for the Subwindow class
subWindow::subWindow(QWidget *parent)
  : QWidget(parent)
{
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  //gameSpace warudo;
  //warudo.setGeometry(100, 100, 700, 575);
  //warudo.show();
  mainWindow mainWin;
  mainWin.setGeometry(100,100,696,570);
  mainWin.show();

  return app.exec();
}
