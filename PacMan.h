#ifndef PACMAN_H
#define PACMAN_H


#include <QColor>
#include <QGraphicsEllipseItem>

class PacMan : public QGraphicsEllipseItem
{
    //PacMan都是圓形的

    public:
        PacMan(int radius , QColor color , double startX , double startY , double endX , double endY , int startSec , int endSec);

        int radius;
        QColor color;
        double startX;
        double startY;
        double endX;
        double endY;
        int startSec;
        int endSec;
};

#endif // PACMAN_H
