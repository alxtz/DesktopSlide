#include <iostream>
#include <QGraphicsScene>
#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include "PacMan.h"

using namespace std;

PacMan::PacMan(int radius, QColor color, double startX, double startY, double endX, double endY, int startSec, int endSec)
 : radius(radius) , color(color) , startX(startX) , startY(startY) , endX(endX) , endY(endY) , startSec(startSec) , endSec(endSec)
{
    moveScale = 1;

    QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(this);

    ellipse->setRect ( -radius , -radius , radius*2 , radius*2 );
    ellipse->setBrush (QBrush(color));
    liveSec = endSec - startSec;
}

PacMan::PacMan(int width, int height, QColor color, double startX, double startY, double endX, double endY, int startSec, int endSec)
 : width(width) , height(height) , color(color) , startX(startX) , startY(startY) , endX(endX) , endY(endY) , startSec(startSec) , endSec(endSec)
{
    moveScale = 1;

    QGraphicsRectItem * rect = new QGraphicsRectItem(this);

    rect->setRect ( -width/2 , -height/2 , width , height );
    rect->setBrush (QBrush(color));
    liveSec = endSec - startSec;
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
