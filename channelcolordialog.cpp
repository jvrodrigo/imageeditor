#include "channelcolordialog.h"

ChannelColorDialog::ChannelColorDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    buttonG = new QGroupBox(tr("Canales"));
    rgb = new QRadioButton(tr("rgb"));
    xyz = new QRadioButton(tr("xyz"));
    ycc = new QRadioButton(tr("ycc"));
    hsv = new QRadioButton(tr("hsv"));
    hls = new QRadioButton(tr("hls"));
    lab = new QRadioButton(tr("lab"));
    luv = new QRadioButton(tr("luv"));

    tLay = new QVBoxLayout();// Layout herramientas

    tLay->addWidget(rgb);
    tLay->addWidget(xyz);
    tLay->addWidget(hsv);
    tLay->addWidget(hls);
    tLay->addWidget(lab);
    tLay->addWidget(luv);


    tLay->addWidget(applyB);
    tLay->addWidget(exitB);

    buttonG->setLayout(tLay);

    setLayout(tLay);
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(rgb,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
    connect(xyz,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
    connect(hsv,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
    connect(hls,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
    connect(lab,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
    connect(luv,SIGNAL(clicked()) ,this,SLOT(viewChannelColor()));
}
void ChannelColorDialog::viewChannelColor(){

    if(rgb->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2BGR);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(xyz->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2XYZ);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(hsv->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2HSV);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(hls->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2HLS);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(lab->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2Lab);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(luv->isChecked()){
        cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2Luv);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
}

void ChannelColorDialog::applyChanges(){

}

void ChannelColorDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

QImage ChannelColorDialog::Mat2QImage(cv::Mat const& src)
{
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

      const float scale = 255.0;

      if (src.depth() == CV_8U) {
        if (src.channels() == 1) {
          for (int i = 0; i < src.rows; ++i) {
            for (int j = 0; j < src.cols; ++j) {
              int level = src.at<quint8>(i, j);
              dest.setPixel(j, i, qRgb(level, level, level));
            }
          }
        } else if (src.channels() == 3) {
          for (int i = 0; i < src.rows; ++i) {
            for (int j = 0; j < src.cols; ++j) {
              cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
              dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
            }
          }
        }
      } else if (src.depth() == CV_32F) {
        if (src.channels() == 1) {
          for (int i = 0; i < src.rows; ++i) {
            for (int j = 0; j < src.cols; ++j) {
              int level = scale * src.at<float>(i, j);
              dest.setPixel(j, i, qRgb(level, level, level));
            }
          }
        } else if (src.channels() == 3) {
          for (int i = 0; i < src.rows; ++i) {
            for (int j = 0; j < src.cols; ++j) {
              cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
              dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
            }
          }
        }
      }

      return dest;
}

cv::Mat ChannelColorDialog::QImage2Mat(QImage const& src)
{
    cv::Mat tmp(src.height(),src.width(),CV_8UC4,(uchar*)src.bits(),src.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cv::cvtColor(tmp, result,CV_BGR2RGB);
    return result;
    /*
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;*/
}
