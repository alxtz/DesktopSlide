#include <QFont>
#include "Clock.h"

Clock::Clock()
{
    amount=1;

    secNow = 0;
    setPlainText (QString::number(secNow));

    setDefaultTextColor(Qt::white);
    setFont(QFont("SansSerif" , 20));
}

void Clock::addSec()
{
    secNow+=amount;
    setPlainText (QString::number(secNow));
}
