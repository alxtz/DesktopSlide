#ifndef STVIEW_H
#define STVIEW_H


#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#include "./StimulateScene.h"
#include "PacManMachine.h"

class StView : public QGraphicsView
{
    Q_OBJECT

    public:
        StView(QWidget * parent = 0);

        StimulateScene * stimulateScene;

        PacManMachine * pacManMachine;

        QString backgroundPath;

        QTimer * moveTimer;

    signals:
        void setSize(int x , int y);

    public slots:
        void addPacMan(PacMan * pacMan);
};

#endif // STVIEW_H
