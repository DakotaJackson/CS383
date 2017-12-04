#ifndef JJDISPLAYOUTPUT_H
#define JJDISPLAYOUTPUT_H

#include <QDialog>
#include <QtGui>
#include <QGraphicsTextItem>
#include <QObject>
#include <QImage>


namespace Ui {
    class JJDisplayOutput;
}

class JJDisplayOutput : public QDialog
{
    Q_OBJECT

public:
    explicit JJDisplayOutput(QWidget *parent = 0, int n = 2, int s = 3, int e = 4, int w = 5);
    ~JJDisplayOutput();
    void initBuilder(int n, int s, int e, int w);
    void step();
    static const int maxCarImages = 3;
    static const int maxLightImages = 3;

protected:
    void paintEvent(QPaintEvent *e);

private:
    void initCars();
    void drawImage(QPainter *qp, int x, int y, int imgIndex, int angle, QImage imgArray[]);
    void drawCars(QPainter *qp);

    void initLights();
    void drawLight(QPainter *qp, int x, int y, int imgIndex, int angle);
    void drawLights(QPainter *qp);

    void initializeRoad();
    void drawRoad(QPainter *qp);

    void drawText(QPainter *qp);

    Ui::JJDisplayOutput *ui;

    //Place holders
    int m_cars[4][4];
    int m_lights[4][4];

    //Image array allocation
    QImage carImage[maxCarImages];
    QImage lightImage[maxLightImages];
    QImage *textImage;

    int m_northLane;
    int m_southLane;
    int m_westLane;
    int m_eastLane;

    int flow = 0;

    const int m_laneWidth = 50;
    const int m_laneLength = 200;

    const int m_lineWidth = 3;
    const int m_lineLength = 10;
};

#endif // JJDISPLAYOUTPUT_H
