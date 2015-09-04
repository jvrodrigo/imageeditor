#ifndef QGLWIDGETDIALOG_H
#define QGLWIDGETDIALOG_H

#include <QGLWidget>
#include <QLCDNumber>
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "myqglwidget.h"
#include "imgwin.h"
#include "qimagecv.h"

class QGLWidgetDialog : public QDialog
{
    Q_OBJECT

public:
    QGLWidgetDialog(ImgWin * parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
    MyQGLWidget *myQGLWidget;
public slots:
    void exit();
    void viewQGLWidget();
    void applyChanges();
private:

    cv::Mat         src;
    QSlider         *slZ;
    QLCDNumber      *dpZ;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QVBoxLayout     *tLay;
};

#endif // QGLWIDGETDIALOG_H
