#ifndef IMGWIN_H
#define IMGWIN_H
#ifndef DEFAULTS
    #define DEFAULTS
    #define DEFAULT_ICON_OPEN   ":/images/icons/open.png"
    #define DEFAULT_ICON_EXIT   ":/images/icons/exit.png"
    #define DEFAULT_ICON_SAVE   ":/images/icons/save.png"
    #define DEFAULT_ICON_FILE   ":/images/icons/main.png"
    #define DEFAULT_IMG_FILE    ":/images/qt-logo.jpg"
    #define DEFAULT_OUTPUT_PATH	"C:/Documents and Settings/Administrator/Desktop"
    #define DEFAULT_IMAGE_PATH	"C:/Documents and Settings/Administrator/Desktop"
#endif
#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include "qimagecv.h"

class ImgWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImgWin(QWidget *parent = 0);
    QImage getMImg();
    QLabel * getLabelImg();
    void setLabelImg(QLabel *label);
    int getAnch();
    QString getFileName();
signals:

public slots:
    void scaleImage(int anch);
    void openFile();
    void saveFile();
private:
    int         anch;
    QString     fname;
    QImage      mImg;
    QLabel      *imgL;
    QLabel      *statusLabel;
    QStatusBar  *statusBar;
    QVBoxLayout *imgLay;
    QWidget     *widg;
};

#endif // IMGWIN_H
