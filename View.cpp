#include <QPixmap>
#include <QBrush>
#include <QImage>
#include <QDebug>
#include "View.h"

View::View(QWidget * parent)
 : QGraphicsView(parent)
{  
    //設定PacManMachine
    pacManMachine = new PacManMachine();
    pacManMachine->readXml ();
    pacManMachine->readCsv ();
    cout<<"pacManList有"<<pacManMachine->pacManList.size ()<<"隻pacMan"<<endl;

    //設定背景圖片
    QString backgroundPath = "./Data/" + pacManMachine->imageFile;
    qDebug()<<"路徑為"<<backgroundPath;


    //設定scene
    stimulateScene = new StimulateScene();
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
}
