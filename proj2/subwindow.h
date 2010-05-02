#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "tutText.h"

//A subwindow class for adding an "action menu"
class actionMenu : public QWidget
{
  Q_OBJECT

public:
  actionMenu(QWidget *parent = 0);

signals:
  void moveOrder();
  void attackOrder();
};

//A subwindow class for adding a "main menu"
class mainMenu : public QWidget
{
  Q_OBJECT

  public:
  mainMenu(QWidget *parent = 0);

signals:
  void tutStart();
};

//A subwindow class for adding a small tutorial window
class smallTutwin : public QWidget
{
  Q_OBJECT

  public:
  smallTutwin(QWidget *parent = 0);

private:
  tutText *textwindow;
};

#endif
