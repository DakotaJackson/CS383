#include "JJDisplayOutput.h"
#include "ui_JJDisplayOutput.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QImage>

JJDisplayOutput::JJDisplayOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JJDisplayOutput)
{
    ui->setupUi(this);
    initCars();
}

JJDisplayOutput::~JJDisplayOutput()
{
    delete ui;
}

void JJDisplayOutput::initializeRoad(int n, int s, int e, int w )
{
    m_northLane = n;
    m_southLane = s;
    m_eastLane = e;
    m_westLane = w;

    resize(m_laneLength + m_laneLength + ((n + s) * m_laneWidth), m_laneLength + m_laneLength + ((w + e) * m_laneWidth));
    show();
    update();
}


void JJDisplayOutput::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);

    drawRoad(&qp);
    drawCars(&qp);
    drawLights(&qp);

    // delete this
    step();
}

void JJDisplayOutput::resizeEvent(QResizeEvent *e)
{


}

void JJDisplayOutput::initCars(){
    for(int i = 0; i < maxCarImages; i++){
        carImage[i].load("C:\\Users\\Joe\\Desktop\\JJDisplayOutput\\car.png");
    }
    carImage[1].load("C:\\Users\\Joe\\Desktop\\JJDisplayOutput\\car2.png");

    //delete this later
    m_cars[0][0]=40;
    m_cars[0][1]=40;
    m_cars[0][2]=0;
    m_cars[0][3]=0;
    m_cars[1][0]=80;
    m_cars[1][1]=80;
    m_cars[1][2]=0;
    m_cars[1][3]=270;

    initializeRoad(1,2,3,4);
}

void JJDisplayOutput::drawCars(QPainter *qp){
    //drawCar(qp,40,40,0,0);
   // drawCar(qp,80,80,0,90);
   // drawCar(qp,120,120,1,180);
   // drawCar(qp,160,160,1,270);
    for(int i=0; i< 2; i++)
    {
        drawCar(qp, m_cars[i][0], m_cars[i][1], m_cars[i][2],m_cars[i][3]);
    }
}

void JJDisplayOutput::drawCar(QPainter *qp, int x, int y, int imgIndex, int angle){
    if(imgIndex >= maxCarImages){
        //error
        return;
    }

    QTransform trans;
    // Move to the center of the image
    trans.translate(x+carImage[imgIndex].width()/2, y+carImage[imgIndex].height()/2);
    trans.rotate(angle);
    qp->setTransform(trans);

    // Draw the image at (0,0), because everything is already handled by the transformation
    qp->drawImage(-carImage[imgIndex].width()/2,-carImage[imgIndex].height()/2,carImage[imgIndex]);
    qp->resetTransform();

}

void JJDisplayOutput::drawLights(QPainter *qp)
{

    int m_northLane = 1;
    int m_southLane = 2;
    int m_westLane = 3;
    int m_eastLane = 4;

    int m_laneWidth = 50;
    int m_laneLength = 200;

    int roadWidthNS = ((m_northLane + m_southLane) * m_laneWidth);
    int roadWidthEW = ((m_westLane + m_eastLane) * m_laneWidth);

    qp->setPen(QColor("#111111"));
    qp->setBrush(QBrush("#111111"));
    //if(int state == 0){
    //    qp->draw
    //}
    //NS Top
    qp->drawRect(m_laneLength, m_laneLength - (m_laneWidth / 2),                       m_laneWidth, 25);
    //NS Bot
    qp->drawRect(m_laneLength + (m_laneWidth * m_northLane), m_laneLength + roadWidthEW, m_laneWidth, 25);
    //EW Left
    qp->drawRect(m_laneLength - 25, m_laneLength + (m_laneWidth * m_westLane),           25, m_laneWidth);
    //EW Right
    qp->drawRect(m_laneLength + roadWidthNS, m_laneLength,                           25, m_laneWidth);
}

void JJDisplayOutput::drawText(QPainter *qp)
{

}

void JJDisplayOutput::step()
{
    m_cars[1][1]++;
    update();
}


void JJDisplayOutput::drawRoad(QPainter *qp){
    
    int roadWidthNS = ((m_northLane + m_southLane) * m_laneWidth);
    int roadWidthEW = ((m_westLane + m_eastLane) * m_laneWidth);

    int screenWidth = roadWidthNS + (m_laneLength * 2);
    int screenHeight = roadWidthEW + (m_laneLength * 2);

    //Background
    qp->setPen(QColor("#00FF00"));
    qp->setBrush(QBrush("#00FF00"));
    qp->drawRect(0,0, screenWidth, screenHeight);

    //***************    Lanes    *****************
    //*********************************************
    //NS
    qp->setPen(QColor("#999999"));
    qp->setBrush(QBrush("#999999"));
    //NS
    qp->drawRect(m_laneLength, 0, roadWidthNS, screenHeight);
    //EW
    qp->drawRect(0, m_laneLength, screenWidth, roadWidthEW);


    //************    Lane markers    *************
    //*********************************************
    qp->setPen(QColor("#FFFFFF"));
    qp->setBrush(QBrush("#FFFFFF"));


    //***************    Borders    ***************
    //*********************************************
    //NS Top
    qp->drawRect(m_laneLength,               0,                         m_lineWidth,  m_laneLength + m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, 0,                         m_lineWidth,  m_laneLength + m_lineWidth);
    //NS Bot
    qp->drawRect(m_laneLength,               screenHeight - m_laneLength, m_lineWidth,  m_laneLength + m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, screenHeight - m_laneLength, m_lineWidth,  m_laneLength + m_lineWidth);
    //EW
    qp->drawRect(0,                        m_laneLength,                m_laneLength, m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, m_laneLength,                m_laneLength, m_lineWidth);
    qp->drawRect(0,                        screenHeight - m_laneLength, m_laneLength, m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, screenHeight - m_laneLength, m_laneLength, m_lineWidth);


    //***************    NS Top    ****************
    //*********************************************
    for(int i = 1; i < m_northLane + m_southLane; i++){
        for(int j = 0; j < 9; j++){
            qp->drawRect(m_laneLength + (m_laneWidth * i), j * 23, m_lineWidth, m_lineLength);
            if(i == m_northLane){
                qp->drawRect(m_laneLength + (m_laneWidth * i), 0, m_lineWidth, m_laneLength + m_lineWidth);
            }
        }
    }
    //***************    NS Bot    ****************
    //*********************************************
    for(int i = 1; i < m_northLane + m_southLane; i++){
        for(int j = 0; j < 9; j++){
            qp->drawRect(m_laneLength + (m_laneWidth * i), (screenHeight - m_laneLength) + (j * 23), m_lineWidth, m_lineLength);
        }
        if(i == m_northLane){
            qp->drawRect(m_laneLength + (m_laneWidth * i), screenHeight - m_laneLength, m_lineWidth, m_laneLength + m_lineWidth);
        }
    }
    //***************    EW Left   ****************
    //*********************************************
    for(int i = 1; i < m_westLane + m_eastLane; i++){
        for(int j = 0; j < 9; j++){
            qp->drawRect(j * 23, m_laneLength + (m_laneWidth * i), m_lineLength, m_lineWidth);
        }
        if(i == m_westLane){
            qp->drawRect(0, m_laneLength + (m_laneWidth * i), m_laneLength + m_lineWidth ,m_lineWidth);
        }
    }
    //***************    EW Right   ***************
    //*********************************************
    for(int i = 1; i < m_westLane + m_eastLane; i++){
        for(int j = 0; j < 9; j++){
            qp->drawRect((screenWidth - m_laneLength) + (j * 23), m_laneLength + (m_laneWidth * i), m_lineLength, m_lineWidth);
        }
        if(i == m_westLane){
            qp->drawRect(screenWidth - m_laneLength, m_laneLength + (m_laneWidth * i), m_laneLength + m_lineWidth ,m_lineWidth);
        }
    }

}
