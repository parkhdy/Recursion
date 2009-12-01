#ifndef LOCALMAP_H
#define LOCALMAP_H

#include <QWidget>
#include <vector>

#include "defs.h"

class localMap : public QWidget
{
  Q_OBJECT

  public:
  localMap(QWidget *parent = 0);

public slots:
  void updateMap(std::vector<std::vector<char> > nextmap);

protected:
  void paintEvent(QPaintEvent *event);

private:
  void paintTile(QPainter &painter, 
                 int row, int col,
                 char type);

  QRect currentTile(int grow, int gcol);

  std::vector<std::vector<char> > cmap;
;
};

#endif
