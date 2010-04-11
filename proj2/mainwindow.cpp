#include "mainwindow.h"

//Constructor for the mainWindow class
mainWindow::mainWindow()
{
  mdiArea = new QMdiArea;
  setCentralWidget(mdiArea);

  theWorld = new gameSpace;
  gateway = new mainMenu;

  connect(theWorld, SIGNAL(showCharwin()), 
         this, SLOT(showActions()));

  connect(gateway, SIGNAL(tutStart()),
          this, SLOT(tutOn()));

  connect(gateway, SIGNAL(tutStart()),
          this, SLOT(closeGate()));

  mdiArea->addSubWindow(gateway);
  gateway->showMaximized();
}
//Slot to make a new game =O
void mainWindow::tutOn()
{
  //std::cout << "Going into tutOn." << std::endl;
  mdiArea->addSubWindow(theWorld);
  theWorld->showMaximized();
}

void mainWindow::closeGate()
{
  gateway->close();
  mdiArea->removeSubWindow(gateway);
}

//Slot to show the subwindow
void mainWindow::showActions()
{
  //std::cout << "Going into addwindow." << std::endl;
  nMenu = new actionMenu;
  nMenu->setAttribute(Qt::WA_DeleteOnClose,true);

  connect(nMenu, SIGNAL(moveOrder()),
          theWorld, SLOT(moveOrderSent()));

  connect(nMenu, SIGNAL(attackOrder()),
          theWorld, SLOT(attackOrderSent()));

  connect(nMenu, SIGNAL(moveOrder()),
          nMenu, SLOT(close()));

  connect(nMenu, SIGNAL(attackOrder()),
          nMenu, SLOT(close()));

  mdiArea->addSubWindow(nMenu);
  nMenu->show();
}

