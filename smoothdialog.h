#ifndef SMOOTHDIALOG_H
#define SMOOTHDIALOG_H

#include <QLCDNumber>
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include "qimagecv.h"
#include "imgwin.h"

class SmoothDialog : public QDialog
{
    Q_OBJECT
public:
    //void closeEvent(QCloseEvent * event);
    ~SmoothDialog();
    SmoothDialog(ImgWin * parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;

signals:

public slots:
    void exit();
    void viewSmooth();
    void applyChanges();
private:
    int             anch;
    cv::Mat         src;
    QSlider         *slSigmaX,*slSigmaY,*slKSize;
    QLCDNumber      *dpSigmaX,*dpSigmaY,*dpKSize;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QGroupBox       *buttonG;
    QRadioButton    *median,*box,*bilateral,*gaussian;
    QVBoxLayout     *tLay;
};

#endif // SMOOTHDIALOG_H
