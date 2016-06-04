#ifndef CLOCK_H
#define CLOCK_H


#include <QGraphicsTextItem>

class Clock : public QGraphicsTextItem
{
    Q_OBJECT

    public:
        Clock();

        int secNow;

        int amount;

        int reloadCycle;

    public slots:
        void addSec();

    signals:
        void reload();
};

#endif // CLOCK_H
