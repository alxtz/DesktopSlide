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
        void sortPacMans();
        void spawnPacMans();

        QTimer  * spawnTimer;
        QString imageFile;
        QString title;
        int reloadCycle;
        double clockPosX , clockPosY;

        vector<PacMan * > pacManList;

        int pacManCount;

    signals:
        void setPacMan(PacMan * );

    public slots:
        void emitSignal();

    private:
        void swapPacMan(int a , int b);
};

#endif // PACMANMACHINE_H
