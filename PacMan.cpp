#include <iostream>
#include <QGraphicsScene>
#include <QBrush>
#include "PacMan.h"

using namespace std;

PacMan::PacMan(int radius, QColor color, double startX, double startY, double endX, double endY, int startSec, int endSec)
 : radius(radius) , color(color) , startX(startX) , startY(startY) , endX(endX) , endY(endY) , startSec(startSec) , endSec(endSec)

{
    moveScale = 1;

    setRect ( -radius , -radius , radius*2 , radius*2 );
    setBrush (QBrush(color));
    liveSec = endSec - startSec;
    cout<<"liveSec為"<<liveSec<<endl;
}

void PacMan::setXYScale(double xScale, double yScale)
{
    this->xScale = xScale;
    this->yScale = yScale;
}

void PacMan::setMoveScale(int scale)
{
    moveScale = scale;
}

void PacMan::move()
{
    setPos(x()+xScale , y()+yScale);
}

void PacMan::destroySelf()
{
    scene()->removeItem (this);
    delete this;
}
