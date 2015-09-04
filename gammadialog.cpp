#include "gammadialog.h"

GammaDialog::GammaDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    // Slider
    slSigma = new QSlider(Qt::Horizontal) ;
    slSigma->setRange(1,1000);
    slSigma->setValue(100);
    slSigma->setToolTip("Sigma");
    dpSigma = new QLCDNumber(3);
    dpSigma->display(100);

    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    tLay = new QVBoxLayout();// Layout herramientas

    tLay->addWidget(dpSigma);
    tLay->addWidget(slSigma);

    tLay->addWidget(applyB);
    tLay->addWidget(exitB);

    setLayout(tLay);

    viewGamma(); // Empieza la funcion ver Gamma

    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slSigma,SIGNAL(valueChanged(int)) , dpSigma , SLOT(display(int)));
    connect(slSigma,SIGNAL(valueChanged(int)) , this,SLOT(viewGamma()));
}

void GammaDialog::viewGamma(){

    double inverse_gamma = 50 / slSigma->value();

    cv::Mat lut_matrix(1, 256, CV_8UC1 );
    uchar * ptr = lut_matrix.ptr();

    for( int i = 0; i < 256; i++ )
    ptr[i] = (int)( cv::pow( (double) i / 255.0, inverse_gamma ) * 255.0 );

    cv::Mat result;
    cv::LUT( QImage2Mat(imgM), lut_matrix, result );

    imgL->setPixmap(QPixmap::fromImage(Mat2QImage(result).scaledToWidth(anch)));

}

void GammaDialog::applyChanges(){

}

void GammaDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

QImage GammaDialog::Mat2QImage(cv::Mat const& src)
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
      /*cv::Mat rgb;
      cv::cvtColor(mat, rgb, CV_BGR2RGB);

      return QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);*/
}

cv::Mat GammaDialog::QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}
