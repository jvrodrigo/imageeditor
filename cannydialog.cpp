#include "cannydialog.h"

CannyDialog::CannyDialog(ImgWin * parent) : QDialog (parent)
{
    imgM = parent->getMImg();// Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    slEdgesLow = new QSlider(Qt::Horizontal) ;
    slEdgesLow->setRange(0,1000);
    slEdgesLow->setValue(50);
    slEdgesLow->setToolTip("Threshold Low");
    disp1 = new QLCDNumber(4);
    disp1->display(50);

    slEdgesHigh = new QSlider(Qt::Horizontal) ;
    slEdgesHigh->setRange(0,1000);
    slEdgesHigh->setValue(50);
    slEdgesHigh->setToolTip("Threshold High");
    disp2 = new QLCDNumber(4);
    disp2->display(50);

    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");
    tLay = new QVBoxLayout();// Layout herramientas
    tLay->addWidget(slEdgesLow);  // Slider resaltar bordes threshold Low
    tLay->addWidget(disp1);         // Display Slider resaltar bordes threshold Low
    tLay->addWidget(slEdgesHigh);  // Slider resaltar bordes threshold High
    tLay->addWidget(disp2);         // Display Slider resaltar bordes threshold High

    tLay->addWidget(applyB);
    tLay->addWidget(exitB);
    setLayout(tLay);

    viewEdges(); // Empieza la función ver bordes

    // Conectores
    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(slEdgesLow,SIGNAL(valueChanged(int)) , disp1 , SLOT(display(int)));
    connect(slEdgesLow,SIGNAL(valueChanged(int)) , this,SLOT(viewEdges()));
    connect(slEdgesHigh,SIGNAL(valueChanged(int)) , disp2 , SLOT(display(int)));
    connect(slEdgesHigh,SIGNAL(valueChanged(int)) , this,SLOT(viewEdges()));
}

CannyDialog::~CannyDialog(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
}

void CannyDialog::applyChanges(){

}

void CannyDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

void CannyDialog::viewEdges()
{
    cv::Mat tmp= QImage2Mat(imgM);
    cv::Mat src = QImage2Mat(imgM);
    cv::cvtColor(tmp,src,CV_RGB2GRAY);
    cv::Canny(src,tmp,slEdgesLow->value(),slEdgesHigh->value(),3);
    imgL->setPixmap(QPixmap::fromImage(Mat2QImage(tmp)).scaledToWidth(anch));
}

QImage CannyDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat CannyDialog::QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}
