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

        QGraphicsRectItem * centerPoint;


        int currentScale = 10000;
        const int scaleMax = 10000;

        int _numScheduledScalings;
        void wheelEvent (QWheelEvent * event);//scroll to resize the view

        void keyPressEvent (QKeyEvent * event);//for testing

        void mousePressEvent      (QMouseEvent * event);//track
        void mouseReleaseEvent (QMouseEvent * event);//track
        void mouseMoveEvent     (QMouseEvent * event);//track
        bool isTracking;//track
        double saveWindowX , saveWindowY;
        double saveDragCenterX , saveDragCenterY;

    signals:
        void setSize(int x , int y);

    public slots:
        void addPacMan(PacMan * pacMan);

        void reload();
};

#endif // STVIEW_H
