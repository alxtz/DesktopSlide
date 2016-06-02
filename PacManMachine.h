#ifndef PACMANMACHINE_H
#define PACMANMACHINE_H


#include <iostream>
#include <vector>
#include <QtXml>
#include <QFile>
#include <QObject>
#include "PacMan.h"

using namespace std;

class PacManMachine : public QObject
{
    Q_OBJECT

    public:
        PacManMachine();
        void readXml();
        void readCsv();


        QString imageFile;
        QString title;
        int reloadCycle;
        double clockPosX , clockPosY;

        vector<PacMan * > pacManList;
};

#endif // PACMANMACHINE_H
