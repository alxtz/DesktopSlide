#ifndef STIMULATESCENE_H
#define STIMULATESCENE_H


#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class StimulateScene : public QGraphicsScene
{
    Q_OBJECT

    public:
        StimulateScene();

        QGraphicsRectItem * rect;

    public slots:
};

#endif // STIMULATESCENE_H
