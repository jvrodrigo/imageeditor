#ifndef CHANNELCOLORDIALOG_H
#define CHANNELCOLORDIALOG_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QDialog>
#include "qimagecv.h"
#include "imgwin.h"

class ChannelColorDialog : public QDialog
{
    Q_OBJECT
public:
    ChannelColorDialog(ImgWin *parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
signals:

public slots:
    void exit();
    void viewChannelColor();
    void applyChanges();

private:
    int             anch;
    cv::Mat         src;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QVBoxLayout     *tLay;
    QGroupBox       *buttonG;
    QRadioButton    *rgb,*xyz,*ycc,*hsv,*hls,*lab,*luv;
};

#endif // CHANNELCOLORDIALOG_H
