#ifndef GAMMADIALOG_H
#define GAMMADIALOG_H
#include <QLCDNumber>
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "qimagecv.h"
#include "imgwin.h"

class GammaDialog : public QDialog
{
    Q_OBJECT
public:
    GammaDialog(ImgWin *parent = 0);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;

signals:

public slots:
    void exit();
    void viewGamma();
    void applyChanges();
private:
    int             anch;
    cv::Mat         src;
    QSlider         *slSigma;
    QLCDNumber      *dpSigma;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QVBoxLayout     *tLay;
};

#endif // GAMMADIALOG_H
