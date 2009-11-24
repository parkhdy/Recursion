#ifndef WORLD_H
#define WORLD_H

#include <QWidget>

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

signals:
  void movedX(int dir, int nXpos);
  void movedY(int dir, int nYpos);

protected:
  void paintEvent(QPaintEvent *event);

private:
  int cXpos;
  int cYpos;
};

#endif
