#include <iostream>
#include <fstream>
#include <QColor>
#include <QTimer>
#include "PacManMachine.h"
#include "PacMan.h"

using namespace std;

PacManMachine::PacManMachine()
{
    spawnTimer = new QTimer();
    spawnTimer->setSingleShot (true);
    spawnTimer->setTimerType (Qt::PreciseTimer);
    //connect ( spawnTimer , SIGNAL(timeout()) , scene , SLOT(addPacMan()) );
}

void PacManMachine::readXml()
{
    cout<<"開始讀xml"<<endl;
    //先開檔
    QFile xmlFile("./Data/config.xml");

    //把開的xml檔案轉成dom文件
    QDomDocument xmlDom;
    xmlDom.setContent (&xmlFile);

    //轉完，關檔
    xmlFile.close ();

    //有了元素，開始讀所需的資料

        //先讀最上層的root元素，instance
        QDomElement instance = xmlDom.documentElement ();

            //讀instance的子元素
            QDomElement childElement = instance.firstChildElement ();

            while(!childElement.isNull())
            {
                cout<<"while"<<endl;
                if(childElement.tagName()=="database")
                {
                    cout<<"database ele"<<endl;
                    //遇到database，不使用，跳出switch，並指定為下個元素
                }
                else if(childElement.tagName()=="background")
                {
                    cout<<"background ele"<<endl;
                    QDomElement GrandChildElement = childElement.firstChildElement ();
                    imageFile = GrandChildElement.attribute ("name");
                }
                else if(childElement.tagName()=="setting")
                {
                    cout<<"setting ele"<<endl;
                    title = childElement.attribute ("title");
                }
                else if(childElement.tagName()=="reload")
                {
                    cout<<"reload ele"<<endl;
                    reloadCycle = childElement.attribute ("cycle").toInt ();
                }
                else if(childElement.tagName()=="clock")
                {
                    cout<<"clokc ele"<<endl;
                    QDomElement GrandChildElement = childElement.firstChildElement ();
                    clockPosX = GrandChildElement.attribute ("x").toDouble ();
                    clockPosY = GrandChildElement.attribute ("y").toDouble ();
                }

                childElement = childElement.nextSiblingElement ();
                cout<<"下一個的tagName為"<<childElement.tagName ().toStdString ()<<endl;
            }

            //讀完xml了
            cout<<"背景的圖片檔名為"<<imageFile.toStdString ()<<endl;
            cout<<"標題名為"<<title.toStdString ()<<endl;
            cout<<"重新載入的週期為"<<reloadCycle<<endl;
            cout<<"時鐘的位置為("<<clockPosX<<","<<clockPosY<<")"<<endl;
}

void PacManMachine::readCsv()
{
    pacManList = new vector<PacMan * >();

    char foo;

    int type;
    int radius;
    int width , height;
    string RGB;
    int R;
    int G;
    int B;
    double startX , startY;
    double endX , endY;
    string startTime;
    string endTime;
    int startSec;
    int endSec;

    ifstream csvFile("./Data/motion.csv");
    while( csvFile>>type )
    {
        csvFile>>foo;
        cout<<"type為"<<type<<endl;
        if(type==1)
        {
            csvFile>>radius>>foo;
            cout<<"半徑為"<<radius<<endl;
        }
        else if(type==2)
        {
            csvFile>>width>>foo>>height>>foo;
        }
        getline(csvFile , RGB , ',' );
        cout<<"RGB為"<<RGB<<endl;
        R = (RGB[0]-48)*100 + (RGB[1]-48)*10 +(RGB[2]-48);
        G = (RGB[3]-48)*100 + (RGB[4]-48)*10 +(RGB[5]-48);
        B = (RGB[6]-48)*100 + (RGB[7]-48)*10 +(RGB[8]-48);
        if(RGB=="0")  R=0 , G=0 , B = 0;
        cout<<"R為"<<R<<",G為"<<G<<",B為"<<B<<endl;
        csvFile>>startX>>foo;
        csvFile>>startY>>foo;
        cout<<"startX為"<<startX<<",startY為"<<startY<<endl;
        csvFile>>endX>>foo;
        csvFile>>endY>>foo;
        cout<<"endX為"<<endX<<",endY為"<<endY<<endl;
        getline(csvFile , startTime , ',' );
        csvFile>>endTime;
        startSec = (startTime[0]-48)*36000
                         + (startTime[1]-48)*3600
                         + (startTime[3]-48)*600
                         + (startTime[4]-48)*60
                         + (startTime[6]-48)*10 +
                         + (startTime[7]-48);
        endSec   = (endTime[0]-48)*36000
                         + (endTime[1]-48)*3600
                         + (endTime[3]-48)*600
                         + (endTime[4]-48)*60
                         + (endTime[6]-48)*10 +
                         + (endTime[7]-48);
        cout<<"startTime為"<<startSec<<",endTime為"<<endSec<<endl;

        if(type==1)
        {
            PacMan * pacMan = new PacMan(radius , QColor(R , G , B) , startX , startY , endX , endY , startSec , endSec);
            pacManList->push_back (pacMan);
        }
        else if(type==2)
        {
            PacMan * pacMan = new PacMan(width , height , QColor(R , G , B) , startX , startY , endX , endY , startSec , endSec);
            pacManList->push_back (pacMan);
        }
    }

}

void PacManMachine::sortPacMans()
{
    for(int i=0; i<pacManList->size(); i++)
    {
        for(int j=1; j<pacManList->size()-i; j++)
        {
            cout<<"比對兩個startSec"<<pacManList->at( j )->startSec<<","<<pacManList->at( j-1)->startSec<<endl;
            if( pacManList->at( j )->startSec < pacManList->at( j-1)->startSec )
            {
                cout<<"調換"<<endl;
                swapPacMan(  j , (j-1) );
            }
        }
    }
}

void PacManMachine::spawnPacMans()
{
    pacManCount = 0;
    for(int i=0; i<pacManList->size (); ++i)
    {
        QTimer::singleShot(pacManList->at(i)->startSec*1000 , this , SLOT(emitSignal()) );
    }
}

void PacManMachine::emitSignal()
{
    emit setPacMan (pacManList->at(pacManCount));
    ++pacManCount;
}

void PacManMachine::swapPacMan(int a, int b)
{
    //cout<<"swap"<<endl;
    //cout<<"原本兩個pacMan的出生時間為"<<pacManList.at( a )<<" , "<<pacManList.at( b )<<endl;
    PacMan * foo;
    foo = pacManList->at(a);
    pacManList->at(a) = pacManList->at(b);
    pacManList->at(b) = foo;
    //cout<<"後來兩個pacMan的出生時間為"<<pacManList.at( a )<<" , "<<pacManList.at( b )<<endl;
}
