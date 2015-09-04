#ifndef CONVOLUTIONFILTER_H
#define CONVOLUTIONFILTER_H

#include <QDialog>
#include <QSlider>
#include <QLCDNumber>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSpinBox>
#include "qimagecv.h"
#include "imgwin.h"

class Filter2DDialog : public QDialog
{
    Q_OBJECT

public:
    ~Filter2DDialog();
    Filter2DDialog(ImgWin *parent = 0);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
signals:

public slots:
    void exit();
    void viewFilter();
    void applyChanges();
private:
    QWidget *widg3x3,*widg5x5;
    QSpinBox        *n00,*n01,*n02,*n03,*n04,
                    *n10,*n11,*n12,*n13,*n14,
                    *n20,*n21,*n22,*n23,*n24,
                    *n30,*n31,*n32,*n33,*n34,
                    *n40,*n41,*n42,*n43,*n44,
                    *n50,*n51,*n52,*n53,*n54;
    QSpinBox        *n500,*n501,*n502,*n503,*n504,
                    *n510,*n511,*n512,*n513,*n514,
                    *n520,*n521,*n522,*n523,*n524,
                    *n530,*n531,*n532,*n533,*n534,
                    *n540,*n541,*n542,*n543,*n544,
                    *n550,*n551,*n552,*n553,*n554;
    int             anch, nMatrix;
    cv::Mat         src;
    QSlider         *slDelta;
    QLCDNumber      *dpDelta;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QGroupBox       *x3Group,*x5Group;
    //QRadioButton    *median,*box,*bilateral,*gaussian;
    QRadioButton    *kernel3x3,*kernel5x5;

    QVBoxLayout     *layMatrix,*tLay,*x3LayPrin,*x5LayPrin;
    QHBoxLayout     *x3Lay0,*x3Lay1,*x3Lay2;
    QHBoxLayout     *x5Lay0,*x5Lay1,*x5Lay2,*x5Lay3,*x5Lay4;
};

#endif // CONVOLUTIONFILTER_H
