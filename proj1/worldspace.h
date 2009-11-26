#ifndef WORLD_H
#define WORLD_H

#include <QWidget>

#define ROW 30
#define COL 30
#define TILESIZE 20

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
  char nextSpace(int dir);
  void paintTile(QPainter &painter, 
                 int row, int col,
                 char type);

  int cXpos;
  int cYpos;
  int cdir; //0 = Up, 1 = Down, 2 = Right, 3 = Left

  QRect currentTile(int grow, int gcol);

  char lvl1[ROW][COL];
};

#endif
