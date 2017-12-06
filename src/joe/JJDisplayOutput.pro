#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T15:37:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JJDisplayOutput
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        JJDisplayOutput.cpp \
    JJTestOutput.cpp \
    DJTrafficLightManager.cpp \
    InputUI.cpp \
    JJDisplayOutput.cpp \
    JJTestOutput.cpp \
    JPCarTestStub.cpp \
    JPIntersection.cpp \
    JPIntersectionExceptions.cpp \
    JPIntersectionGrid.cpp \
    JPLane.cpp \
    JPLightTestStub.cpp \
    JPObservableSimulation.cpp \
    JPOtherException.cpp \
    JPSimulationControler.cpp \
    JPSimulationEngine.cpp \
    JPTrafficLightAdapter.cpp \
    JPTrafficModel.cpp \
    JPTrafficModelExceptions.cpp \
    JPUpdatableInterface.cpp \
    LinkedList.cpp \
    main.cpp \
    SFCarGen.cpp

HEADERS += \
        JJDisplayOutput.h \
    JJTestOutput.h \
    DJTrafficLightManager.h \
    JJDisplayOutput.h \
    JJTestOutput.h \
    JPCarTestStub.h \
    JPConstants.h \
    JPIntersection.h \
    JPIntersectionExceptions.h \
    JPIntersectionGrid.h \
    JPLane.h \
    JPLightTestStub.h \
    JPObservableSimulation.h \
    JPOtherException.h \
    JPSimulationControler.h \
    JPSimulationEngine.h \
    JPTrafficLightAdapter.h \
    JPTrafficModel.h \
    JPTrafficModelExceptions.h \
    JPUpdatableInterface.h \
    SFCarGen.h

FORMS += \
        JJDisplayOutput.ui \
    JJInputui.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
