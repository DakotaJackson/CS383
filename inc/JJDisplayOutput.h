#ifndef JJDISPLAYOUTPUT_H
#define JJDISPLAYOUTPUT_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QImage>
#include <JJInputui.h>


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
    static const int maxLightImages = 3;

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    void initCars();
    void drawCar(QPainter *qp, int x, int y, int imgIndex, int angle);
    void drawCars(QPainter *qp);

    void initLights();
    void drawLight(QPainter *qp, int x, int y, int imgIndex, int angle);
    void drawLights(QPainter *qp);

    void drawRoad(QPainter *qp);
    void drawText(QPainter *qp);

    Ui::JJDisplayOutput *ui;

    int m_cars[4][4];
    int m_lights[3][3];
    QImage carImage[maxCarImages];
    QImage lightImage[maxLightImages];
    QImage *textImage;

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
