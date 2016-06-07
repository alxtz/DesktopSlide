#include <iostream>
#include <QBrush>
#include <QColor>
#include "StimulateScene.h"

using namespace std;

StimulateScene::StimulateScene()
{
    //pacManCount = 0;

    //set testing rect
    rect = new QGraphicsRectItem();
    rect->setRect ( 0 , 0 , 100 , 100);
    addItem(rect);
    rect->setBrush (QBrush(QColor(Qt::red)));
}
