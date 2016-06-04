#include <iostream>
#include <QPixmap>
#include <QBrush>
#include <QImage>
#include <QDebug>
#include <QTimeLine>
#include "StView.h"

using namespace std;

StView::StView(QWidget * parent)
 : QGraphicsView(parent)
{
    //設定視窗
    setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

    //設定moveTimer
    moveTimer = new QTimer();
    moveTimer->setTimerType (Qt::PreciseTimer);
    moveTimer->start (25);

    //設定scene
    stimulateScene = new StimulateScene();

    //設定PacManMachine
    pacManMachine = new PacManMachine();
    connect (pacManMachine , SIGNAL(setPacMan(PacMan * )) , this , SLOT(addPacMan(PacMan *)) );
    pacManMachine->readXml ();
    pacManMachine->readCsv ();
    cout<<"pacManList有"<<pacManMachine->pacManList->size ()<<"隻pacMan"<<endl;
    pacManMachine->sortPacMans ();
    for(int i=0; i<6; ++i)
    {
        cout<<"第"<<i+1<<"隻pacMan的startSec為"<<pacManMachine->pacManList->at(i)->startSec<<endl;
    }

    //設定背景圖片
    backgroundPath = "./Data/" + pacManMachine->imageFile;
    qDebug()<<"路徑為"<<backgroundPath;

    //設定scene
    stimulateScene->setSceneRect ( 0 , 0 , QImage(backgroundPath).width () , QImage(backgroundPath).height ());
    stimulateScene->setBackgroundBrush (QBrush(QImage(backgroundPath)));
    setScene (stimulateScene);


    //設定View
    setFixedSize (QImage(backgroundPath).width ()+2 , QImage(backgroundPath).height ()+2 );
    connect (this , SIGNAL(setSize(int,int)) , parent , SLOT(setSize(int,int)) );
    emit setSize ( QImage(backgroundPath).width ()+2 , QImage(backgroundPath).height ()+2 );
    cout<<"emited"<<endl;

    //設定title
    parent->setWindowTitle (pacManMachine->title);

    //設定clock
    clock = new Clock();
    clock->setPos (QImage(backgroundPath).width() * pacManMachine->clockPosX , QImage(backgroundPath).height() * pacManMachine->clockPosY);
    clockTimer = new QTimer();
    clockTimer->setTimerType (Qt::PreciseTimer);
    connect(clockTimer , SIGNAL(timeout()) , clock , SLOT(addSec()) );
    connect(clock , SIGNAL(reload()) , this , SLOT(reload()) );

    //開始模擬
    pacManMachine->spawnPacMans ();
    clockTimer->start(1000);
    stimulateScene->addItem (clock);
}

void StView::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        cout<<"放大"<<endl;
        currentScale+=event->delta();
    }
    else
    {
        cout<<"縮小"<<endl;
        currentScale+=event->delta();
    }

    if(currentScale<scaleMax)
    {
        cout<<"拉回來"<<endl;
        currentScale-=event->delta();
        return;
    }

    double factor = event->delta()/100.0;
    if(event->delta()>0)
    {
        factor = factor;
    }
    else
    {
        factor = -1/factor;
    }

    scale(factor , factor);

    cout<<"currentScale為"<<currentScale<<endl;
}

void StView::addPacMan(PacMan * pacMan)
{
    int x = (double)QImage(backgroundPath).width() * pacMan->startX;
    int y = (double)QImage(backgroundPath).height() * pacMan->startY;
    pacMan->setPos( x , y );




    //以第一號來說
    //x座標要在，(6-2)4秒之內，走圖片寬度*(0.9-0.05)
    //然後timer每次跑是跑0.1秒

    int runSec = pacMan->liveSec;
    double runLengthX = (double)QImage(backgroundPath).width() * (pacMan->endX - pacMan->startX);
    double runLengthY = (double)QImage(backgroundPath).height () * (pacMan->endY - pacMan->startY);

    double xScale = ((double)runLengthX / runSec ) / (1000/moveTimer->interval ());
    double yScale = ((double)runLengthY / runSec ) / (1000/moveTimer->interval ());

    pacMan->setXYScale (xScale , yScale);

    stimulateScene->addItem(pacMan);
    //QTimer::singleShot ( pacMan->liveSec *1000 , pacMan , SLOT(destroySelf()) );
    QTimer * timer = new QTimer();
    timer->setTimerType (Qt::PreciseTimer);
    connect(timer , SIGNAL(timeout()) , pacMan , SLOT(destroySelf()) );
    timer->start (pacMan->liveSec *1000);
    connect(moveTimer , SIGNAL(timeout()) , pacMan , SLOT(move()) );
}

void StView::reload()
{
    pacManMachine->readCsv ();
    pacManMachine->sortPacMans ();
    pacManMachine->spawnPacMans ();
}
