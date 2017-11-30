#include "JJDisplayOutput.h"
#include "ui_JJDisplayOutput.h"

//#include "JPIntersection.h"
//#include "JPLane.h"

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
    initLights();
}

JJDisplayOutput::~JJDisplayOutput()
{
    delete ui;
}

void JJDisplayOutput::initializeRoad(int n, int s, int e, int w )
{
    //JPIntersection j;
    //m_northLane = j.getLaneCount(1);

    //m_southLane = JPIntersection.getLaneCount(2);
    //m_eastLane = JPIntersection.getLaneCount(3);
    //m_westLane = JPIntersection.getLaneCount(4);

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
  /*
*/
    initializeRoad(1,2,3,4);
}


void JJDisplayOutput::drawCars(QPainter *qp){

    // in JPIntersection
    JPLane *testLane = something.getLane();
    int laneCount = something.getLaneCount(direction);

    // in JPLane
    /* int size = something.getSize();
     * SFCar *testCar = something.getNextCar();
     */

    // in SFCar
    /* int carX = something.getX();
     * int carY = something.getY();
     * int angle = something.getTheta();
     *
     *
     * for(int i = 0; i < size; i++)
     * {
     *       drawCar(qp, m_cars[i][0], m_cars[i][1], m_cars[i][2], m_cars[i][3]);
     *
     */

    for(int i=0; i< 4; i++)
    {
        drawCar(qp, m_cars[i][0], m_cars[i][1], m_cars[i][2], m_cars[i][3]);
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

void JJDisplayOutput::initLights()
{
    lightImage[0].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightRed.png");
    lightImage[1].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightYellow.png");
    lightImage[2].load("C:\\Users\\0.0\\Desktop\\JJDisplayOutput\\lightGreen.png");


    m_lights[0][0]=180;
    m_lights[0][1]=200;
    m_lights[0][2]=0;
    m_lights[0][3]=0;
 /*
    m_lights[1][0]=200;
    m_lights[1][1]=200;
    m_lights[1][2]=1;
    m_lights[1][3]=0;

    m_lights[2][0]=200;
    m_lights[2][1]=600;
    m_lights[2][2]=1;
    m_lights[2][3]=180;

    m_lights[3][0]=200;
    m_lights[3][1]=200;
    m_lights[3][2]=2;
    m_lights[3][3]=270;

*/
}

void JJDisplayOutput::drawLights(QPainter *qp)
{

    for(int i=0; i < 1; i++)
    {
        /*int testState = something.getState(i?,??,??);
        testState = testState - 1;
        if(testState == 4)
        {
                testState = testState - 2;
        }
        drawLight(qp, m_lights[i][0],  m_lights[i][1],  m_lights[i][testState], m_lights[i][3]);
        */
        drawLight(qp, m_lights[i][0],  m_lights[i][1],  m_lights[i][2], m_lights[i][3]);

    }
}

void JJDisplayOutput::drawLight(QPainter *qp, int x, int y, int imgIndex, int angleLight)
{
    if(imgIndex >= maxLightImages){
        //error
        return;
    }

    QTransform lightTrans;
    // Move to the center of the image


    lightTrans.translate(x+lightImage[imgIndex].width()/2, y+lightImage[imgIndex].height()/2);
    lightTrans.rotate(angleLight);
    qp->setTransform(lightTrans);

    // Draw the image at (0,0), because everything is already handled by the transformation
    qp->drawImage(-lightImage[imgIndex].width()/2,-lightImage[imgIndex].height()/2,lightImage[imgIndex]);
    qp->resetTransform();

/*
    int roadWidthNS = ((m_northLane + m_southLane) * m_laneWidth);
    int roadWidthEW = ((m_westLane + m_eastLane) * m_laneWidth);

    //NS Top
    qp->drawRect(m_laneLength, m_laneLength - (m_laneWidth / 2),                       m_laneWidth, 25);
    //NS Bot
    qp->drawRect(m_laneLength + (m_laneWidth * m_northLane), m_laneLength + roadWidthEW, m_laneWidth, 25);
    //EW Left
    qp->drawRect(m_laneLength - 25, m_laneLength + (m_laneWidth * m_westLane),           25, m_laneWidth);
    //EW Right
    qp->drawRect(m_laneLength + roadWidthNS, m_laneLength,                           25, m_laneWidth);

*/

}

void JJDisplayOutput::drawRoad(QPainter *qp){
    //QRect rec(10,10,100,100);
    //QPen framePen(Qt::red);

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

void JJDisplayOutput::drawText(QPainter *qp)
{

}


void JJDisplayOutput::step()
{
    m_cars[0][0]++;
    update();
}


void JJDisplayOutput::on_pushButton_clicked()
{

}
