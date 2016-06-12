#ifndef STVIEW_H
#define STVIEW_H


#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include "./StimulateScene.h"
#include "Clock.h"
#include "PacManMachine.h"


class StView : public QGraphicsView
{
    Q_OBJECT

    public:
        StView(QWidget * parent = 0);

        StimulateScene * stimulateScene;

        PacManMachine * pacManMachine;

        Clock * clock;

        QString backgroundPath;

        QTimer * moveTimer;
        QTimer * clockTimer;

    signals:
        void setSize(int , int);

    public slots:
        void addPacMan(PacMan * pacMan);

        void reload();

    //the part to handle scroll and drag
    public:
        void wheelEvent (QWheelEvent * event);
        void mousePressEvent      (QMouseEvent * event);
        void mouseReleaseEvent (QMouseEvent * event);
        void mouseMoveEvent     (QMouseEvent * event);

        double saveWindowX;
        double saveWindowY;

        double saveCenterX;
        double saveCenterY;

        double lastdx;
        double lastdy;

        double scaleNow;

        bool isDrag;
};

#endif // STVIEW_H
