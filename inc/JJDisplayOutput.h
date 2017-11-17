#ifndef JJDISPLAYOUTPUT_H
#define JJDISPLAYOUTPUT_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QImage>



namespace Ui {
    class JJDisplayOutput;
}

class JJDisplayOutput : public QDialog
{
    Q_OBJECT

public:
    explicit JJDisplayOutput(QWidget *parent = 0);
    ~JJDisplayOutput();
    void initializeRoad(int n, int s, int e, int w);
    void step();
    static const int maxCarImages = 5;

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    void initCars();
    void drawRoad(QPainter *qp);
    void drawCar(QPainter *qp, int x, int y, int imgIndex, int angle);
    void drawCars(QPainter *qp);
    void drawLights(QPainter *qp);
    void drawText(QPainter *qp);
    Ui::JJDisplayOutput *ui;
    
    //placeholder for cars
    int m_cars[2][4]; //for now 2/4
    
    QImage carImage[maxCarImages];
    QImage *redCar;
    QImage *lightImage;
    QImage *textImage;

    //placeholder for lanes
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
