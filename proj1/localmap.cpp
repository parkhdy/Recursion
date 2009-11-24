#include <QPainter>

#include "localmap.h"

localMap::localMap(QWidget *parent)
  : QWidget(parent)
{
  setPalette(QPalette(QColor(250, 250, 200)));
  setAutoFillBackground(true);
}
