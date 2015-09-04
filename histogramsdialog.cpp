#include "histogramsdialog.h"

HistogramsDialog::HistogramsDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg();
    src = QImage2Mat(imgM); // Pasa la imagen al la matriz src
    histL = new QLabel(); // Label para mostrar el histograma
    anch = parent->getAnch();   // Toma el ancho de la imagen

    saveB = new QPushButton("Aplicar");
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

    tLay->addWidget(histL);
    tLay->addWidget(rgb);
    tLay->addWidget(xyz);
    tLay->addWidget(hsv);
    tLay->addWidget(hls);
    tLay->addWidget(lab);
    tLay->addWidget(luv);

    tLay->addWidget(saveB);
    tLay->addWidget(exitB);

    buttonG->setLayout(tLay);

    setLayout(tLay);

    rgb->setChecked(true);
    viewHistograms();

    connect(saveB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(rgb,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
    connect(xyz,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
    connect(hsv,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
    connect(hls,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
    connect(lab,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
    connect(luv,SIGNAL(clicked()) ,this,SLOT(viewHistograms()));
}

void HistogramsDialog::applyChanges(){

}

void HistogramsDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}
void HistogramsDialog::calculateHistogram(cv::Mat mat){
    cv::vector<cv::Mat> bgr_planes;
    cv::split( mat, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true;
    bool accumulate = false;

    cv::Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    cv::calcHist( &bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    cv::calcHist( &bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    // Draw the histograms for B, G and R
    int hist_w = 300; int hist_h = 300;
    int bin_w = cvRound( (double) hist_w/histSize );

    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                      cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                      cv::Scalar( 255, 0, 0), 2, 8, 0  );
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                      cv::Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                      cv::Scalar( 0, 255, 0), 2, 8, 0  );
        cv::line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                      cv::Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                      cv::Scalar( 0, 0, 255), 2, 8, 0  );
 }

 /// Display
 ///
 histL->setPixmap(QPixmap::fromImage(Mat2QImage(histImage)));
}

void HistogramsDialog::viewHistograms(){
    if(rgb->isChecked()){
        //cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2BGR);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(xyz->isChecked()){
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2XYZ);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(hsv->isChecked()){
        //cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2HSV);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(hls->isChecked()){
        //cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2HLS);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(lab->isChecked()){
        //cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2Lab);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(luv->isChecked()){
        //cv::Mat src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2Luv);
        calculateHistogram(dst);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }


}

QImage HistogramsDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat HistogramsDialog::QImage2Mat(QImage const& src)
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
