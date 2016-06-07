#include <QFont>
#include "Clock.h"

Clock::Clock()
{
    amount=1;

    reloadCycle = 2000;

    secNow = 0;
    setPlainText (QString::number(secNow));

    setDefaultTextColor(Qt::white);
    setFont(QFont("SansSerif" , 20));
}

void Clock::addSec()
{
    secNow+=amount;
    setPlainText (QString::number(secNow));

    if(secNow==reloadCycle)
    {
        secNow = 0;
        setPlainText (QString::number(secNow));
        emit reload();
    }
}
