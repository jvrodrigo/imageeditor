#ifndef SOBELDIALOG_H
#define SOBELDIALOG_H

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

class EdgesDialog : public QDialog
{
    Q_OBJECT
public:
    EdgesDialog(ImgWin *parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
signals:

public slots:
    void exit();
    void viewEdges();
    void applyChanges();
private:
    int             anch;
    cv::Mat         src;
    QSlider         *slAlpha,*slBeta,*slGamma;
    QLCDNumber      *dpAlpha,*dpBeta,*dpGamma;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QGroupBox       *buttonG;
    QRadioButton    *robertsB, *prewitB, *sobelB, *scharrB, *laplacianaB,*logB;
    QVBoxLayout     *tLay;
};

#endif // SOBELDIALOG_H
