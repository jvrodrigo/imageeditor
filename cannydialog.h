#ifndef EDGESDIALOG_H
#define EDGESDIALOG_H
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>
#include <QDialog>
#include <QVBoxLayout>
#include "qimagecv.h"
#include "imgwin.h"

class CannyDialog: public QDialog
{
    Q_OBJECT

signals:

private slots:
    void exit();
    void viewEdges();
    void applyChanges();
public:
    ~CannyDialog();
    CannyDialog (ImgWin * parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;

private:
    int             anch;
    QLabel      *imgL;
    QPushButton *applyB,*exitB;
    QSlider     *slEdgesLow,*slEdgesHigh;
    QLCDNumber  *disp1,*disp2;
    QVBoxLayout *tLay;
};

#endif // EDGESDIALOG_H
