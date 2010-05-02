#include "mainwindow.h"

//Constructor for the mainWindow class
mainWindow::mainWindow()
{
  mdiArea = new QMdiArea;
  mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation,true);
  setCentralWidget(mdiArea);

  gateway = new mainMenu(mdiArea);
  theWorld = new gameSpace;

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
  sTutwin = new smallTutwin(mdiArea);

  mdiArea->addSubWindow(theWorld);
  theWorld->showMaximized();
  theWorld->startTutorial();

  mdiArea->addSubWindow(sTutwin);
  sTutwin->show();
}

void mainWindow::closeGate()
{
  gateway->close();
  mdiArea->removeSubWindow(gateway);
}

void mainWindow::closeAction()
{
  nMenu->close();
  mdiArea->removeSubWindow(nMenu);
}

//Slot to show the subwindow
void mainWindow::showActions()
{
  //std::cout << "Going into addwindow." << std::endl;
  nMenu = new actionMenu(mdiArea);

  connect(nMenu, SIGNAL(moveOrder()),
          theWorld, SLOT(moveOrderSent()));

  connect(nMenu, SIGNAL(attackOrder()),
          theWorld, SLOT(attackOrderSent()));

  connect(nMenu, SIGNAL(moveOrder()),
          this, SLOT(closeAction()));

  connect(nMenu, SIGNAL(attackOrder()),
          this, SLOT(closeAction()));

  mdiArea->addSubWindow(nMenu);
  nMenu->show();
}

