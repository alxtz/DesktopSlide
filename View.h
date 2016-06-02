#ifndef VIEW_H
#define VIEW_H


#include <QObject>
#include <QGraphicsView>
#include "./StimulateScene.h"
#include "PacManMachine.h"

class View : public QGraphicsView
{
    Q_OBJECT

    public:
        View(QWidget * parent = 0);

        StimulateScene * stimulateScene;
        PacManMachine * pacManMachine;

    signals:
        void setSize(int x , int y);
};

#endif // VIEW_H
