#ifndef CIRCLE_H
#define CIRCLE_H


#include <QColor>
#include <QGraphicsEllipseItem>

class Circle : QGraphicsEllipseItem
{
    //圓形的type為1

    public:
        Circle();

    private:
        int radius;
        QColor * color;
        double startX , startY , endX , endY;
        char startTime[9];
        char endTime[9];
};

#endif // CIRCLE_H
