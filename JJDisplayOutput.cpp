#include "JJDisplayOutput.h"
#include "ui_JJDisplayOutput.h"

#include "JPIntersection.h"
#include "JPLane.h"
#include "SFCarGen.h"

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QImage>

JJDisplayOutput::JJDisplayOutput(QWidget *parent, int n, int s, int e, int w) :
    QDialog(parent),
    ui(new Ui::JJDisplayOutput)
{
    ui->setupUi(this);
    initBuilder(n, s, e, w);
}

JJDisplayOutput::JJDisplayOutput(JPIntersection *intersect, JPLane *lane)
{
    m_tempIntersect = intersect;
    m_tempLane = lane;
}

JJDisplayOutput::~JJDisplayOutput()
{
    delete ui;
}

//Virtual QT function that is automatically called on update within step
void JJDisplayOutput::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);

    drawRoad(&qp);
    drawCars(&qp);
    drawLights(&qp);

    // delete this when timer is implemented
    step();
}

//Get lane settings, resize screen to lane size
void JJDisplayOutput::initRoad()
{
    resize(m_laneLength + m_laneLength + ((m_northLane + m_southLane) * m_laneWidth), m_laneLength + m_laneLength + ((m_westLane + m_eastLane) * m_laneWidth));
    show();
    update();
}

//Get car images
void JJDisplayOutput::initCars(){
    carImage[0].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\car1.png");
    carImage[1].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\car2.png");
    carImage[2].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\car3.png");
    /*
    for(int i = 0; i < maxCarImages; i++){
        carImage[i].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\car1.png");
    }
    carImage[1].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\car2.png");
    */
    //delete this later
    m_cars[0][0]=0;
    m_cars[0][1]=200;
    m_cars[0][2]=0;
    m_cars[0][3]=0;

    m_cars[1][0]=100;
    m_cars[1][1]=200;
    m_cars[1][2]=0;
    m_cars[1][3]=180;

    m_cars[2][0]=200;
    m_cars[2][1]=200;
    m_cars[2][2]=0;
    m_cars[2][3]=90;

    m_cars[3][0]=300;
    m_cars[3][1]=200;
    m_cars[3][2]=0;
    m_cars[3][3]=270;

    m_cars[4][0]=400;
    m_cars[4][1]=200;
    m_cars[4][2]=0;
    m_cars[4][3]=0;
}

//Get light images
void JJDisplayOutput::initLights()
{
    lightImage[0].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightRed.png");
    lightImage[1].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightYellow.png");
    lightImage[2].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightGreen.png");

    //theta 0 = facing north
    //Eastbound light (Left)
    m_lights[0][0]=m_laneLength - 20;
    m_lights[0][1]=m_laneLength + (m_laneWidth * m_westLane) + 3;
    m_lights[0][2]=1;
    m_lights[0][3]=0;

    //Northbound light (Bottom)
    m_lights[1][0]=m_laneLength + (m_laneWidth * m_northLane) + 20;
    m_lights[1][1]=m_laneLength + (m_laneWidth * (m_westLane + m_eastLane)) - 15;
    m_lights[1][2]=2;
    m_lights[1][3]=90;

    //Westbound light (Right)
    m_lights[2][0]=m_laneLength + (m_laneWidth * (m_northLane + m_southLane));
    m_lights[2][1]=m_laneLength + 3;
    m_lights[2][2]=2;
    m_lights[2][3]=180;

    //Southbound light (Top)
    m_lights[3][0]=m_laneLength + 20;
    m_lights[3][1]=m_laneLength - 35;
    m_lights[3][2]=1;
    m_lights[3][3]=270;

}

//Walks through car list and draws them
void JJDisplayOutput::drawCars(QPainter *qp){

    int n = m_tempIntersect->getLaneCount(0);
    int e = m_tempIntersect->getLaneCount(1);
    int s = m_tempIntersect->getLaneCount(2);
    int w = m_tempIntersect->getLaneCount(3);

    int size = m_tempLane->getSize();

    for(int j = 0; j < n; j++){
        for(int i = 0; i < size; i++){
            Car *car = m_tempLane->getNextCar();
            int x = car->getX();
            int y = car->getY();
            int theta = car->getTheta();
            int length = car->getLength();
            drawImage(qp, x, y, length, theta, carImage);
        }
    }

    /*
    for(int i=0; i< 4; i++)
    {
        drawImage(qp, m_cars[i][0], m_cars[i][1], m_cars[i][2], m_cars[i][3], carImage);
    }
    */
}

//Walks through light list and draws them
void JJDisplayOutput::drawLights(QPainter *qp)
{

    /*int testState = something.getState(i?,??,??);
    testState = testState - 1;
    if(testState == 4)
    {
            testState = testState - 2;
    }
    drawLight(qp, m_lights[i][0],  m_lights[i][1],  m_lights[i][testState], m_lights[i][3]);
    */

    for(int i=0; i< 4; i++)
    {
        drawImage(qp, m_lights[i][0],  m_lights[i][1],  m_lights[i][2], m_lights[i][3], lightImage);
    }
}

//Walks through lane parameters and draws road
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
    qp->drawRect(m_laneLength,               0,                           m_lineWidth,  m_laneLength + m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, 0,                           m_lineWidth,  m_laneLength + m_lineWidth);
    //NS Bot
    qp->drawRect(m_laneLength,               screenHeight - m_laneLength, m_lineWidth,  m_laneLength + m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, screenHeight - m_laneLength, m_lineWidth,  m_laneLength + m_lineWidth);
    //EW
    qp->drawRect(0,                          m_laneLength,                m_laneLength, m_lineWidth);
    qp->drawRect(m_laneLength + roadWidthNS, m_laneLength,                m_laneLength, m_lineWidth);
    qp->drawRect(0,                          screenHeight - m_laneLength, m_laneLength, m_lineWidth);
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

//Gets throughput and draws it
void JJDisplayOutput::drawText(QPainter *qp)
{

}

//Draws images with pivot point adjusted to center of image
void JJDisplayOutput::drawImage(QPainter *qp, int x, int y, int imgIndex, int angle, QImage imgArray[]){
    if(imgIndex >= maxCarImages || imgIndex >= maxLightImages){
        //error
        return;
    }

    QTransform trans;
    // Move to the center of the image


    trans.translate(x+imgArray[imgIndex].width()/2, y+imgArray[imgIndex].height()/2);
    trans.rotate(angle);
    qp->setTransform(trans);

    // Draw the image at (0,0), because everything is already handled by the transformation
    qp->drawImage(-imgArray[imgIndex].width()/2,-imgArray[imgIndex].height()/2,imgArray[imgIndex]);
    qp->resetTransform();

}

//Initializes all images
void JJDisplayOutput::initBuilder(int n, int s, int e, int w)
{
    m_northLane = n;
    m_southLane = s;
    m_eastLane = e;
    m_westLane = w;
    initCars();
    initLights();
    initRoad();
}

//Increments paintevent
void JJDisplayOutput::step()
{
    m_cars[0][0]++;
    update();
}
