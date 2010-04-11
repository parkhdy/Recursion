#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>
#include <QLabel>
#include <vector>
#include <QMdiArea>
#include <QMainWindow>

#include "mainwindow.h"
#include "gamespace.h"
#include "worldspace.h"
#include "worldtree.h"
#include "localmap.h"
#include "tile.h"

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
