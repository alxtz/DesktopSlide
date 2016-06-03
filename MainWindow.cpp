#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
{
    view = new StView(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setSize(int x, int y)
{
    cout<<"setMainWindow"<<endl;
    setFixedSize (x , y);
}
