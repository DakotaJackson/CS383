#ifndef JJDISPLAYOUTPUT_H
#define JJDISPLAYOUTPUT_H

#include <QDialog>
#include <QtGui>
#include <QGraphicsTextItem>
#include <QObject>
#include <QImage>
#include "JPIntersection.h"

namespace Ui {
    class JJDisplayOutput;
}

class JJDisplayOutput : public QDialog
{
    Q_OBJECT

public:
    explicit JJDisplayOutput(QWidget *parent = 0, int n = 2, int s = 3, int e = 4, int w = 5);
    JJDisplayOutput(JPIntersection *intersect, JPLane *lane);
    ~JJDisplayOutput();

    void initBuilder(int n, int s, int e, int w);   //Set up builder pattern
    void step();                                    //Increment draw functions

    //Max number of images to load
    static const int maxCarImages = 3;
    static const int maxLightImages = 3;


protected:
    //Virtual QT function
    void paintEvent(QPaintEvent *e);

private:
    void initRoad();    //Get lane settings
    void initCars();    //Load car images
    void initLights();  //Load light images

    void drawCars(QPainter *qp);    //Steps through car list drawing cars
    void drawLights(QPainter *qp);  //Steps through light list drawing lights
    void drawRoad(QPainter *qp);    //Steps through lane list drawing lanes
    void drawText(QPainter *qp);    //Gets throughput and displays

    //Draw images, moves pivot to center of image, resets on return.
    void drawImage(QPainter *qp, int x, int y, int imgIndex, int angle, QImage imgArray[]);

    Ui::JJDisplayOutput *ui;

    //Place holders
    int m_cars[4][4];
    int m_lights[4][4];

    //Image array allocation
    QImage carImage[maxCarImages];
    QImage lightImage[maxLightImages];
    QImage *textImage;

    //Traffic flow counter
    int flow = 0;

    //Lane draw parameters
    int m_northLane;
    int m_southLane;
    int m_westLane;
    int m_eastLane;

    const int m_laneWidth = 50;
    const int m_laneLength = 200;

    const int m_lineWidth = 3;
    const int m_lineLength = 10;
};

#endif // JJDISPLAYOUTPUT_H
