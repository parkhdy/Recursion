#ifndef TUTTEXTWIN_H
#define TUTTEXTWIN_H

#include <QWidget>
#include <sstream>

#include "defs.h"
#include "unit.h"

class tutText : public QWidget
{
  Q_OBJECT

  public:
  tutText(QWidget *parent = 0);

protected:
  void updateText();
  void paintEvent(QPaintEvent *event);
};

#endif
