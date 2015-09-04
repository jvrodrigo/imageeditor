#ifndef HISTOGRAMSDIALOG_H
#define HISTOGRAMSDIALOG_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QDialog>
#include "qimagecv.h"
#include "imgwin.h"

class HistogramsDialog : public QDialog
{
    Q_OBJECT
public:
    HistogramsDialog(ImgWin * parent);
    void        calculateHistogram(cv::Mat mat);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
signals:

public slots:
    void exit();
    void viewHistograms();
    void applyChanges();

private:
    int             anch;
    cv::Mat         src;
    QLabel          *histL,*imgL;
    QPushButton     *saveB, *exitB;
    QVBoxLayout     *tLay;
    QGroupBox       *buttonG;
    QRadioButton    *rgb,*xyz,*ycc,*hsv,*hls,*lab,*luv;
};

#endif // HISTOGRAMSDIALOG_H
