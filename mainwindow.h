#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSlider>
#include <QLCDNumber>
#include "imgwin.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ImgWin *imgW;
signals:

public slots:
    void startChannelColorDialog();
    void startHistogramsDialog();
    void startEdgesDialog();
    void startBlobsDialog();
    void startCannyDialog();
    void startSmoothDialog();
    void startGammaDialog();
    void startFilter2DDialog();
    void startQGLWidgetDialog();
private:
    QLCDNumber      *dpSize;
    QSlider         *slSize;
    QVBoxLayout     *layPrin,*layF1,*layF2,*laySize;
    QHBoxLayout     *layFile,*layFilters,*layQGLWidget;
    QPushButton     *qglWidgetB,*channelB,*histogramsB,*smoothB,*cannyB,
                    *blobsB,*gammaB,*filter2DB, *edgesB,
                    *exitB, *openB, *saveB;
    QWidget         *mWid;
    QPixmap         *img;
};

#endif // MAINWINDOW_H
