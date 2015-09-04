#include "edgesdialog.h"

EdgesDialog::EdgesDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    src = QImage2Mat(imgM);
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    // Slider
    slAlpha = new QSlider(Qt::Horizontal) ;
    slAlpha->setRange(0,20);
    slAlpha->setValue(2);
    slAlpha->setToolTip("Alpha");
    dpAlpha = new QLCDNumber(2);
    dpAlpha->display(2);
    slBeta = new QSlider(Qt::Horizontal) ;
    slBeta->setRange(0,20);
    slBeta->setValue(2);
    slBeta->setToolTip("Beta");
    dpBeta = new QLCDNumber(2);
    dpBeta->display(2);
    slGamma = new QSlider(Qt::Horizontal) ;
    slGamma->setRange(0,255);
    slGamma->setValue(0);
    slGamma->setToolTip("Gamma");
    dpGamma = new QLCDNumber(3);
    dpGamma->display(0);
    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    buttonG = new QGroupBox(tr("Canales"));
    robertsB = new QRadioButton(tr("Roberts"));
    prewitB = new QRadioButton(tr("Prewit"));
    sobelB = new QRadioButton(tr("Sobel"));
    scharrB = new QRadioButton(tr("Scharr"));
    laplacianaB = new QRadioButton(tr("Laplace"));
    logB = new QRadioButton(tr("Log"));

    tLay = new QVBoxLayout();// Layout herramientas

    tLay->addWidget(dpAlpha);
    tLay->addWidget(slAlpha);
    tLay->addWidget(dpBeta);
    tLay->addWidget(slBeta);
    tLay->addWidget(dpGamma);
    tLay->addWidget(slGamma);
    tLay->addWidget(robertsB);
    tLay->addWidget(prewitB);
    tLay->addWidget(sobelB);
    tLay->addWidget(scharrB);
    tLay->addWidget(laplacianaB);
    tLay->addWidget(logB);

    tLay->addWidget(applyB);
    tLay->addWidget(exitB);
    buttonG->setLayout(tLay);
    setLayout(tLay);

    viewEdges(); // Empieza la funcion ver Sobel

    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slAlpha,SIGNAL(valueChanged(int)) , dpAlpha , SLOT(display(int)));
    connect(slAlpha,SIGNAL(valueChanged(int)) , this,SLOT(viewEdges()));
    connect(slBeta,SIGNAL(valueChanged(int)) , dpBeta , SLOT(display(int)));
    connect(slBeta,SIGNAL(valueChanged(int)) , this,SLOT(viewEdges()));
    connect(slGamma,SIGNAL(valueChanged(int)) , dpGamma , SLOT(display(int)));
    connect(slGamma,SIGNAL(valueChanged(int)) , this,SLOT(viewEdges()));
    connect(robertsB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
    connect(prewitB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
    connect(sobelB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
    connect(scharrB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
    connect(laplacianaB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
    connect(logB,SIGNAL(clicked()) , this,SLOT(viewEdges()));
}
void EdgesDialog::applyChanges(){

}

void EdgesDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}
void EdgesDialog::viewEdges(){
    int ddepth = CV_16S;
    int scale = 1;
    int delta = 0;
    if(robertsB->isChecked()){

    }
    else if(prewitB->isChecked()){

        cv::Mat dst,tmp;

        cv::cvtColor( src,tmp , CV_RGB2GRAY );
       /* cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                          1.f/16, 2.f/16, 1.f/16,
                          2.f/16, 4.f/16, 2.f/16,
                          1.f/16, 2.f/16, 1.f/16);*/
        cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                                 -1, 0, -1,
                                 -1, 0, -1,
                                 -1, 0, -1);

        cv::filter2D( tmp, dst, CV_32F,kernel, cv::Point(-1,-1),slGamma->value(),cv::BORDER_DEFAULT);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(sobelB->isChecked()){

        cv::Mat src_gray;
        cv::Mat gaussian;
        cv::GaussianBlur( src, gaussian, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );

        /// Convert it to gray
        cv::cvtColor( gaussian, src_gray, CV_RGB2GRAY );

        /// Generate grad, grad_x and grad_y

        cv::Mat grad, grad_x, grad_y;
        cv::Mat abs_grad_x, abs_grad_y;

        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        cv::Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        cv::Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( grad_y, abs_grad_y );

          /// Total Gradient (approximate)
        cv::addWeighted( abs_grad_x, slAlpha->value(), abs_grad_y, slBeta->value(), slGamma->value(), grad );
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(grad)).scaledToWidth(anch));
    }
    else if(scharrB->isChecked()){

    }
    else if(laplacianaB->isChecked()){

        cv::Mat dst;

        cv::Laplacian(src,dst,CV_32F,1,slAlpha->value(),slBeta->value());
        cv::cvtColor( dst, dst, CV_RGB2GRAY );
        cv::convertScaleAbs(dst,dst,slAlpha->value(),slBeta->value());

        cv::blur( dst, dst,cv::Size(3,3));
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(logB->isChecked()){
        // Constroi kernel Gauss; todas entradas = 1/16
        src = QImage2Mat(imgM);
        cv::Mat dst;
        cv::GaussianBlur(src,dst,cv::Size(3,3),slAlpha->value(),slBeta->value());
        cv::cvtColor( dst, dst, CV_RGB2GRAY );
        cv::Laplacian(dst,dst,CV_32F,1,slAlpha->value(),slBeta->value());
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
}

QImage EdgesDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat EdgesDialog::QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}

