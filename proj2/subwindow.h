#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

//A subwindow class for adding a menu
class actionMenu : public QWidget
{
  Q_OBJECT

public:
  actionMenu(QWidget *parent = 0);

signals:
  void moveOrder();
  void attackOrder();
};

class mainMenu : public QWidget
{
  Q_OBJECT

  public:
  mainMenu(QWidget *parent = 0);

signals:
  void tutStart();
};

#endif
