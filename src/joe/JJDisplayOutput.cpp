#include "JJDisplayOutput.h"
#include "ui_JJDisplayOutput.h"


JJDisplayOutput::JJDisplayOutput(QWidget *parent) : ui(new Ui::JJDisplayOutput)
{
    ui->setupUi(this);
}

JJDisplayOutput::~JJDisplayOutput()
{
    delete ui;
}

void JJDisplayOutput::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter qp(this);

    initializeRoad(&qp);
}

void JJDisplayOutput::initializeRoad(QPainter *qp){

}


void JJDisplayOutput::drawLights(QGraphicsPixmapItem *qp){

}

void JJDisplayOutput::drawCars(QGraphicsItem *p){

}


void JJDisplayOutput::updateStats(QGraphicsItem *p)
{

}