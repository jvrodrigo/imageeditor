#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T17:15:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qimagecv.cpp \
    imgwin.cpp \
    blobsdialog.cpp \
    channelcolordialog.cpp \
    histogramsdialog.cpp \
    smoothdialog.cpp \
    cannydialog.cpp \
    edgesdialog.cpp \
    gammadialog.cpp \
    filter2Ddialog.cpp \
    qglwidgetdialog.cpp \
    myqglwidget.cpp

HEADERS  += mainwindow.h \
         qimagecv.h \
    imgwin.h \
    blobsdialog.h \
    channelcolordialog.h \
    histogramsdialog.h \
    smoothdialog.h \
    cannydialog.h \
    edgesdialog.h \
    gammadialog.h \
    filter2Ddialog.h \
    qglwidgetdialog.h \
    myqglwidget.h

INCLUDEPATH += D:/Qt/opencv-build/install/include


LIBS += -LD:\\Qt\\opencv-build\\bin \
    libopencv_core249d \
    libopencv_highgui249d \
    libopencv_imgproc249d \
    libopencv_features2d249d \
    libopencv_calib3d249d \

FORMS    += mainwindow.ui

RESOURCES += \
    imageeditor.qrc

