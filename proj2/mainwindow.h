#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMdiArea>
#include <QMainWindow>
#include <iostream>

#include "gamespace.h"
#include "subwindow.h"

class QMdiArea;

//The "mainwindow" class, which is a Qmdiarea
class mainWindow : public QMainWindow
{
  Q_OBJECT

  public:
  mainWindow();

public slots:
  void tutOn();
  void closeGate();
  void showActions();

private:
  QMdiArea *mdiArea;
  gameSpace *theWorld;
  mainMenu *gateway;
  actionMenu *nMenu;
};

#endif
