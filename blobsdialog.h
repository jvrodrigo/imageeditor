#ifndef BLOBSDIALOG_H
#define BLOBSDIALOG_H
#include <QLCDNumber>
#include <QDialog>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "qimagecv.h"
#include "imgwin.h"

class BlobsDialog : public QDialog
{
    Q_OBJECT
public:
    BlobsDialog(ImgWin * parent);
    cv::Mat     QImage2Mat(QImage const& src);
    QImage      Mat2QImage(cv::Mat const& src);
    QImage      imgM;
signals:

public slots:
    void exit();
    void viewBlobs();
    void applyChanges();
private:
    int             anch;
    void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
    std::vector <std::vector<cv::Point2i> > blobs;
    cv::Mat         src;
    QSlider         *slthreshold;
    QLCDNumber      *disp;
    QLabel          *imgL;
    QPushButton     *applyB, *exitB;
    QVBoxLayout     *tLay;

};

#endif // BLOBSDIALOG_H
