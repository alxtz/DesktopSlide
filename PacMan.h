#ifndef PACMAN_H
#define PACMAN_H


#include <QObject>
#include <QColor>
#include <QGraphicsEllipseItem>

class PacMan : public QObject , public QGraphicsEllipseItem
{
    Q_OBJECT

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
        int liveSec;


        double xScale;
        double yScale;
        void setXYScale(double xScale , double yScale);

        int moveScale;
        void setMoveScale(int scale);

    public slots:
        void move();
        void destroySelf();
};

#endif // PACMAN_H
