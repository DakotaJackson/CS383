/********************************************************************************
** Form generated from reading UI file 'jjinputui.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef INPUTUI_H
#define INPUTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *okButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *eLane5_l;
    QCheckBox *sLane4_l;
    QCheckBox *sLane3_l;
    QCheckBox *nLane2_l;
    QCheckBox *sLane2_l;
    QCheckBox *wLane3_l;
    QCheckBox *sLane2_r;
    QCheckBox *wLane5_l;
    QCheckBox *eLane2_l;
    QCheckBox *nLane3_l;
    QCheckBox *nLane4_l;
    QLabel *turnOptions_2;
    QCheckBox *wLane1_r;
    QCheckBox *eLane2_r;
    QCheckBox *eLane3_l;
    QCheckBox *nLane1_r;
    QCheckBox *eLane1_r;
    QCheckBox *sLane1_r;
    QCheckBox *wLane4_l;
    QCheckBox *wLane1_l;
    QCheckBox *sLane5_l;
    QCheckBox *eLane4_l;
    QCheckBox *nLane5_l;
    QCheckBox *wLane2_r;
    QCheckBox *eLane4_r;
    QSpinBox *cph;
    QLabel *carsPerHour;
    QSpinBox *ewSpeedLim;
    QSpinBox *nsSpeedLim;
    QLabel *label_5;
    QLabel *speedLimit;
    QSpinBox *nTurnProb_w;
    QSpinBox *nTurnProb_e;
    QSpinBox *sTurnProb_s;
    QSpinBox *nTurnProb_s;
    QLabel *profOfTurn_s;
    QSpinBox *wTurnProb_r;
    QSpinBox *eTurnProb_r;
    QSpinBox *sTurnProb_r;
    QSpinBox *nTurnProb_r;
    QLabel *probOfTurn_r;
    QSpinBox *wTurnProb_l;
    QSpinBox *eTurnProb_l;
    QSpinBox *sTurnProb_l;
    QSpinBox *nTurnProb_l;
    QLabel *probOfTurn_l;
    QCheckBox *wLane5_r;
    QCheckBox *eLane5_r;
    QCheckBox *sLane5_r;
    QCheckBox *nLane5_r;
    QCheckBox *wLane4_r;
    QCheckBox *sLane4_r;
    QCheckBox *wLane2_l;
    QCheckBox *nLane3_r;
    QCheckBox *sLane3_r;
    QCheckBox *eLane3_r;
    QCheckBox *nLane4_r;
    QCheckBox *wLane3_r;
    QCheckBox *nLane2_r;
    QCheckBox *eLane1_l;
    QCheckBox *sLane1_l;
    QSpinBox *nLanes;
    QDoubleSpinBox *nOffset;
    QSpinBox *eLanes;
    QLabel *label_4;
    QCheckBox *nLane1_l;
    QLabel *numOfLanes;
    QSpinBox *wLanes;
    QLabel *turnOptions;
    QLabel *laneOffset;
    QDoubleSpinBox *sOffset;
    QDoubleSpinBox *wOffset;
    QSpinBox *sLanes;
    QDoubleSpinBox *eOffset;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(358, 506);
        okButton = new QDialogButtonBox(Dialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(10, 470, 341, 32));
        okButton->setOrientation(Qt::Horizontal);
        okButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 342, 446));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        eLane5_l = new QCheckBox(layoutWidget);
        eLane5_l->setObjectName(QStringLiteral("eLane5_l"));

        gridLayout->addWidget(eLane5_l, 7, 3, 1, 1);

        sLane4_l = new QCheckBox(layoutWidget);
        sLane4_l->setObjectName(QStringLiteral("sLane4_l"));

        gridLayout->addWidget(sLane4_l, 6, 2, 1, 1);

        sLane3_l = new QCheckBox(layoutWidget);
        sLane3_l->setObjectName(QStringLiteral("sLane3_l"));

        gridLayout->addWidget(sLane3_l, 5, 2, 1, 1);

        nLane2_l = new QCheckBox(layoutWidget);
        nLane2_l->setObjectName(QStringLiteral("nLane2_l"));

        gridLayout->addWidget(nLane2_l, 4, 1, 1, 1);

        sLane2_l = new QCheckBox(layoutWidget);
        sLane2_l->setObjectName(QStringLiteral("sLane2_l"));

        gridLayout->addWidget(sLane2_l, 4, 2, 1, 1);

        wLane3_l = new QCheckBox(layoutWidget);
        wLane3_l->setObjectName(QStringLiteral("wLane3_l"));

        gridLayout->addWidget(wLane3_l, 5, 4, 1, 1);

        sLane2_r = new QCheckBox(layoutWidget);
        sLane2_r->setObjectName(QStringLiteral("sLane2_r"));

        gridLayout->addWidget(sLane2_r, 9, 2, 1, 1);

        wLane5_l = new QCheckBox(layoutWidget);
        wLane5_l->setObjectName(QStringLiteral("wLane5_l"));

        gridLayout->addWidget(wLane5_l, 7, 4, 1, 1);

        eLane2_l = new QCheckBox(layoutWidget);
        eLane2_l->setObjectName(QStringLiteral("eLane2_l"));

        gridLayout->addWidget(eLane2_l, 4, 3, 1, 1);

        nLane3_l = new QCheckBox(layoutWidget);
        nLane3_l->setObjectName(QStringLiteral("nLane3_l"));

        gridLayout->addWidget(nLane3_l, 5, 1, 1, 1);

        nLane4_l = new QCheckBox(layoutWidget);
        nLane4_l->setObjectName(QStringLiteral("nLane4_l"));

        gridLayout->addWidget(nLane4_l, 6, 1, 1, 1);

        turnOptions_2 = new QLabel(layoutWidget);
        turnOptions_2->setObjectName(QStringLiteral("turnOptions_2"));

        gridLayout->addWidget(turnOptions_2, 8, 0, 1, 1);

        wLane1_r = new QCheckBox(layoutWidget);
        wLane1_r->setObjectName(QStringLiteral("wLane1_r"));

        gridLayout->addWidget(wLane1_r, 8, 4, 1, 1);

        eLane2_r = new QCheckBox(layoutWidget);
        eLane2_r->setObjectName(QStringLiteral("eLane2_r"));

        gridLayout->addWidget(eLane2_r, 9, 3, 1, 1);

        eLane3_l = new QCheckBox(layoutWidget);
        eLane3_l->setObjectName(QStringLiteral("eLane3_l"));

        gridLayout->addWidget(eLane3_l, 5, 3, 1, 1);

        nLane1_r = new QCheckBox(layoutWidget);
        nLane1_r->setObjectName(QStringLiteral("nLane1_r"));

        gridLayout->addWidget(nLane1_r, 8, 1, 1, 1);

        eLane1_r = new QCheckBox(layoutWidget);
        eLane1_r->setObjectName(QStringLiteral("eLane1_r"));

        gridLayout->addWidget(eLane1_r, 8, 3, 1, 1);

        sLane1_r = new QCheckBox(layoutWidget);
        sLane1_r->setObjectName(QStringLiteral("sLane1_r"));

        gridLayout->addWidget(sLane1_r, 8, 2, 1, 1);

        wLane4_l = new QCheckBox(layoutWidget);
        wLane4_l->setObjectName(QStringLiteral("wLane4_l"));

        gridLayout->addWidget(wLane4_l, 6, 4, 1, 1);

        wLane1_l = new QCheckBox(layoutWidget);
        wLane1_l->setObjectName(QStringLiteral("wLane1_l"));

        gridLayout->addWidget(wLane1_l, 3, 4, 1, 1);

        sLane5_l = new QCheckBox(layoutWidget);
        sLane5_l->setObjectName(QStringLiteral("sLane5_l"));

        gridLayout->addWidget(sLane5_l, 7, 2, 1, 1);

        eLane4_l = new QCheckBox(layoutWidget);
        eLane4_l->setObjectName(QStringLiteral("eLane4_l"));

        gridLayout->addWidget(eLane4_l, 6, 3, 1, 1);

        nLane5_l = new QCheckBox(layoutWidget);
        nLane5_l->setObjectName(QStringLiteral("nLane5_l"));

        gridLayout->addWidget(nLane5_l, 7, 1, 1, 1);

        wLane2_r = new QCheckBox(layoutWidget);
        wLane2_r->setObjectName(QStringLiteral("wLane2_r"));

        gridLayout->addWidget(wLane2_r, 9, 4, 1, 1);

        eLane4_r = new QCheckBox(layoutWidget);
        eLane4_r->setObjectName(QStringLiteral("eLane4_r"));

        gridLayout->addWidget(eLane4_r, 11, 3, 1, 1);

        cph = new QSpinBox(layoutWidget);
        cph->setObjectName(QStringLiteral("cph"));

        gridLayout->addWidget(cph, 18, 1, 1, 1);

        carsPerHour = new QLabel(layoutWidget);
        carsPerHour->setObjectName(QStringLiteral("carsPerHour"));

        gridLayout->addWidget(carsPerHour, 18, 0, 1, 1);

        ewSpeedLim = new QSpinBox(layoutWidget);
        ewSpeedLim->setObjectName(QStringLiteral("ewSpeedLim"));

        gridLayout->addWidget(ewSpeedLim, 17, 2, 1, 1);

        nsSpeedLim = new QSpinBox(layoutWidget);
        nsSpeedLim->setObjectName(QStringLiteral("nsSpeedLim"));

        gridLayout->addWidget(nsSpeedLim, 17, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 16, 1, 1, 2);

        speedLimit = new QLabel(layoutWidget);
        speedLimit->setObjectName(QStringLiteral("speedLimit"));

        gridLayout->addWidget(speedLimit, 16, 0, 1, 1);

        nTurnProb_w = new QSpinBox(layoutWidget);
        nTurnProb_w->setObjectName(QStringLiteral("nTurnProb_w"));
        nTurnProb_w->setMaximum(100);

        gridLayout->addWidget(nTurnProb_w, 15, 4, 1, 1);

        nTurnProb_e = new QSpinBox(layoutWidget);
        nTurnProb_e->setObjectName(QStringLiteral("nTurnProb_e"));
        nTurnProb_e->setMaximum(100);

        gridLayout->addWidget(nTurnProb_e, 15, 3, 1, 1);

        sTurnProb_s = new QSpinBox(layoutWidget);
        sTurnProb_s->setObjectName(QStringLiteral("sTurnProb_s"));
        sTurnProb_s->setMaximum(100);

        gridLayout->addWidget(sTurnProb_s, 15, 2, 1, 1);

        nTurnProb_s = new QSpinBox(layoutWidget);
        nTurnProb_s->setObjectName(QStringLiteral("nTurnProb_s"));
        nTurnProb_s->setMaximum(100);

        gridLayout->addWidget(nTurnProb_s, 15, 1, 1, 1);

        profOfTurn_s = new QLabel(layoutWidget);
        profOfTurn_s->setObjectName(QStringLiteral("profOfTurn_s"));

        gridLayout->addWidget(profOfTurn_s, 15, 0, 1, 1);

        wTurnProb_r = new QSpinBox(layoutWidget);
        wTurnProb_r->setObjectName(QStringLiteral("wTurnProb_r"));
        wTurnProb_r->setMaximum(100);

        gridLayout->addWidget(wTurnProb_r, 14, 4, 1, 1);

        eTurnProb_r = new QSpinBox(layoutWidget);
        eTurnProb_r->setObjectName(QStringLiteral("eTurnProb_r"));
        eTurnProb_r->setMaximum(100);

        gridLayout->addWidget(eTurnProb_r, 14, 3, 1, 1);

        sTurnProb_r = new QSpinBox(layoutWidget);
        sTurnProb_r->setObjectName(QStringLiteral("sTurnProb_r"));
        sTurnProb_r->setMaximum(100);

        gridLayout->addWidget(sTurnProb_r, 14, 2, 1, 1);

        nTurnProb_r = new QSpinBox(layoutWidget);
        nTurnProb_r->setObjectName(QStringLiteral("nTurnProb_r"));
        nTurnProb_r->setMaximum(100);

        gridLayout->addWidget(nTurnProb_r, 14, 1, 1, 1);

        probOfTurn_r = new QLabel(layoutWidget);
        probOfTurn_r->setObjectName(QStringLiteral("probOfTurn_r"));

        gridLayout->addWidget(probOfTurn_r, 14, 0, 1, 1);

        wTurnProb_l = new QSpinBox(layoutWidget);
        wTurnProb_l->setObjectName(QStringLiteral("wTurnProb_l"));
        wTurnProb_l->setMaximum(100);

        gridLayout->addWidget(wTurnProb_l, 13, 4, 1, 1);

        eTurnProb_l = new QSpinBox(layoutWidget);
        eTurnProb_l->setObjectName(QStringLiteral("eTurnProb_l"));
        eTurnProb_l->setMaximum(100);

        gridLayout->addWidget(eTurnProb_l, 13, 3, 1, 1);

        sTurnProb_l = new QSpinBox(layoutWidget);
        sTurnProb_l->setObjectName(QStringLiteral("sTurnProb_l"));
        sTurnProb_l->setMaximum(100);

        gridLayout->addWidget(sTurnProb_l, 13, 2, 1, 1);

        nTurnProb_l = new QSpinBox(layoutWidget);
        nTurnProb_l->setObjectName(QStringLiteral("nTurnProb_l"));
        nTurnProb_l->setMaximum(100);

        gridLayout->addWidget(nTurnProb_l, 13, 1, 1, 1);

        probOfTurn_l = new QLabel(layoutWidget);
        probOfTurn_l->setObjectName(QStringLiteral("probOfTurn_l"));

        gridLayout->addWidget(probOfTurn_l, 13, 0, 1, 1);

        wLane5_r = new QCheckBox(layoutWidget);
        wLane5_r->setObjectName(QStringLiteral("wLane5_r"));

        gridLayout->addWidget(wLane5_r, 12, 4, 1, 1);

        eLane5_r = new QCheckBox(layoutWidget);
        eLane5_r->setObjectName(QStringLiteral("eLane5_r"));

        gridLayout->addWidget(eLane5_r, 12, 3, 1, 1);

        sLane5_r = new QCheckBox(layoutWidget);
        sLane5_r->setObjectName(QStringLiteral("sLane5_r"));

        gridLayout->addWidget(sLane5_r, 12, 2, 1, 1);

        nLane5_r = new QCheckBox(layoutWidget);
        nLane5_r->setObjectName(QStringLiteral("nLane5_r"));

        gridLayout->addWidget(nLane5_r, 12, 1, 1, 1);

        wLane4_r = new QCheckBox(layoutWidget);
        wLane4_r->setObjectName(QStringLiteral("wLane4_r"));

        gridLayout->addWidget(wLane4_r, 11, 4, 1, 1);

        sLane4_r = new QCheckBox(layoutWidget);
        sLane4_r->setObjectName(QStringLiteral("sLane4_r"));

        gridLayout->addWidget(sLane4_r, 11, 2, 1, 1);

        wLane2_l = new QCheckBox(layoutWidget);
        wLane2_l->setObjectName(QStringLiteral("wLane2_l"));

        gridLayout->addWidget(wLane2_l, 4, 4, 1, 1);

        nLane3_r = new QCheckBox(layoutWidget);
        nLane3_r->setObjectName(QStringLiteral("nLane3_r"));

        gridLayout->addWidget(nLane3_r, 10, 1, 1, 1);

        sLane3_r = new QCheckBox(layoutWidget);
        sLane3_r->setObjectName(QStringLiteral("sLane3_r"));

        gridLayout->addWidget(sLane3_r, 10, 2, 1, 1);

        eLane3_r = new QCheckBox(layoutWidget);
        eLane3_r->setObjectName(QStringLiteral("eLane3_r"));

        gridLayout->addWidget(eLane3_r, 10, 3, 1, 1);

        nLane4_r = new QCheckBox(layoutWidget);
        nLane4_r->setObjectName(QStringLiteral("nLane4_r"));

        gridLayout->addWidget(nLane4_r, 11, 1, 1, 1);

        wLane3_r = new QCheckBox(layoutWidget);
        wLane3_r->setObjectName(QStringLiteral("wLane3_r"));

        gridLayout->addWidget(wLane3_r, 10, 4, 1, 1);

        nLane2_r = new QCheckBox(layoutWidget);
        nLane2_r->setObjectName(QStringLiteral("nLane2_r"));

        gridLayout->addWidget(nLane2_r, 9, 1, 1, 1);

        eLane1_l = new QCheckBox(layoutWidget);
        eLane1_l->setObjectName(QStringLiteral("eLane1_l"));

        gridLayout->addWidget(eLane1_l, 3, 3, 1, 1);

        sLane1_l = new QCheckBox(layoutWidget);
        sLane1_l->setObjectName(QStringLiteral("sLane1_l"));

        gridLayout->addWidget(sLane1_l, 3, 2, 1, 1);

        nLanes = new QSpinBox(layoutWidget);
        nLanes->setObjectName(QStringLiteral("nLanes"));
        nLanes->setMaximum(6);

        gridLayout->addWidget(nLanes, 1, 1, 1, 1);

        nOffset = new QDoubleSpinBox(layoutWidget);
        nOffset->setObjectName(QStringLiteral("nOffset"));
        nOffset->setDecimals(1);
        nOffset->setMaximum(2.5);
        nOffset->setSingleStep(0.5);

        gridLayout->addWidget(nOffset, 2, 1, 1, 1);

        eLanes = new QSpinBox(layoutWidget);
        eLanes->setObjectName(QStringLiteral("eLanes"));
        eLanes->setMaximum(6);

        gridLayout->addWidget(eLanes, 1, 3, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 4);

        nLane1_l = new QCheckBox(layoutWidget);
        nLane1_l->setObjectName(QStringLiteral("nLane1_l"));

        gridLayout->addWidget(nLane1_l, 3, 1, 1, 1);

        numOfLanes = new QLabel(layoutWidget);
        numOfLanes->setObjectName(QStringLiteral("numOfLanes"));

        gridLayout->addWidget(numOfLanes, 1, 0, 1, 1);

        wLanes = new QSpinBox(layoutWidget);
        wLanes->setObjectName(QStringLiteral("wLanes"));
        wLanes->setMaximum(6);
        wLanes->setValue(0);

        gridLayout->addWidget(wLanes, 1, 4, 1, 1);

        turnOptions = new QLabel(layoutWidget);
        turnOptions->setObjectName(QStringLiteral("turnOptions"));

        gridLayout->addWidget(turnOptions, 3, 0, 1, 1);

        laneOffset = new QLabel(layoutWidget);
        laneOffset->setObjectName(QStringLiteral("laneOffset"));

        gridLayout->addWidget(laneOffset, 2, 0, 1, 1);

        sOffset = new QDoubleSpinBox(layoutWidget);
        sOffset->setObjectName(QStringLiteral("sOffset"));
        sOffset->setDecimals(1);
        sOffset->setMaximum(2.5);
        sOffset->setSingleStep(0.5);

        gridLayout->addWidget(sOffset, 2, 2, 1, 1);

        wOffset = new QDoubleSpinBox(layoutWidget);
        wOffset->setObjectName(QStringLiteral("wOffset"));
        wOffset->setMaximum(2.5);
        wOffset->setSingleStep(0.5);

        gridLayout->addWidget(wOffset, 2, 4, 1, 1);

        sLanes = new QSpinBox(layoutWidget);
        sLanes->setObjectName(QStringLiteral("sLanes"));
        sLanes->setMaximum(6);

        gridLayout->addWidget(sLanes, 1, 2, 1, 1);

        eOffset = new QDoubleSpinBox(layoutWidget);
        eOffset->setObjectName(QStringLiteral("eOffset"));
        eOffset->setMaximum(2.5);
        eOffset->setSingleStep(0.5);

        gridLayout->addWidget(eOffset, 2, 3, 1, 1);


        retranslateUi(Dialog);
        QObject::connect(okButton, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(okButton, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        eLane5_l->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        sLane4_l->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        sLane3_l->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        nLane2_l->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        sLane2_l->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        wLane3_l->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        sLane2_r->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        wLane5_l->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        eLane2_l->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        nLane3_l->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        nLane4_l->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        turnOptions_2->setText(QApplication::translate("Dialog", "Turn Option R", nullptr));
        wLane1_r->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        eLane2_r->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        eLane3_l->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        nLane1_r->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        eLane1_r->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        sLane1_r->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        wLane4_l->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        wLane1_l->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        sLane5_l->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        eLane4_l->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        nLane5_l->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        wLane2_r->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        eLane4_r->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        carsPerHour->setText(QApplication::translate("Dialog", "Cars per hour", nullptr));
        label_5->setText(QApplication::translate("Dialog", "    N / S           E / W", nullptr));
        speedLimit->setText(QApplication::translate("Dialog", "Speed Limit", nullptr));
        profOfTurn_s->setText(QApplication::translate("Dialog", "Probability of turn S", nullptr));
        probOfTurn_r->setText(QApplication::translate("Dialog", "Probability of turn R", nullptr));
        probOfTurn_l->setText(QApplication::translate("Dialog", "Probability of turn L", nullptr));
        wLane5_r->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        eLane5_r->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        sLane5_r->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        nLane5_r->setText(QApplication::translate("Dialog", "Lane 5", nullptr));
        wLane4_r->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        sLane4_r->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        wLane2_l->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        nLane3_r->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        sLane3_r->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        eLane3_r->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        nLane4_r->setText(QApplication::translate("Dialog", "Lane 4", nullptr));
        wLane3_r->setText(QApplication::translate("Dialog", "Lane 3", nullptr));
        nLane2_r->setText(QApplication::translate("Dialog", "Lane 2", nullptr));
        eLane1_l->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        sLane1_l->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        label_4->setText(QApplication::translate("Dialog", "      N                  S                   E                 W", nullptr));
        nLane1_l->setText(QApplication::translate("Dialog", "Lane 1", nullptr));
        numOfLanes->setText(QApplication::translate("Dialog", "Number of lanes", nullptr));
        turnOptions->setText(QApplication::translate("Dialog", "Turn Option L", nullptr));
        laneOffset->setText(QApplication::translate("Dialog", "Lane Offset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // INPUTUI_H
