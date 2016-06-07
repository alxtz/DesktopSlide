#ifndef PACMAN_H
#define PACMAN_H


#include <QObject>
#include <QColor>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>

class PacMan : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT

    //PacMan都是圓形的

    public:
        PacMan(int radius , QColor color , int layer , double startX , double startY , double endX , double endY , int startSec , int endSec);
        PacMan(int width , int height ,  QColor color , int layer , double startX , double startY , double endX , double endY , int startSec , int endSec);

        int radius;
        int width , height;
        QColor color;

        int layer;

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
