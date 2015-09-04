#include "smoothdialog.h"

SmoothDialog::SmoothDialog(ImgWin * parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    // Sliders
    slSigmaX = new QSlider(Qt::Horizontal) ;
    slSigmaX->setRange(0,1500);
    slSigmaX->setValue(0);
    slSigmaX->setToolTip("Sigma X");
    dpSigmaX = new QLCDNumber(3);
    dpSigmaX->display(0);

    slSigmaY = new QSlider(Qt::Horizontal) ;
    slSigmaY->setRange(0,100);
    slSigmaY->setValue(0);
    slSigmaY->setToolTip("Sigma Y");
    dpSigmaY = new QLCDNumber(3);
    dpSigmaY->display(0);

    slKSize = new QSlider(Qt::Horizontal) ;
    slKSize->setRange(2,31);
    slKSize->setValue(3);
    slKSize->setSingleStep(2);

    slKSize->setToolTip("Kernel Size");
    dpKSize = new QLCDNumber(2);
    dpKSize->display(3);

    buttonG = new QGroupBox(tr("Canales"));
    box = new QRadioButton(tr("caja"));
    median = new QRadioButton(tr("mediana"));
    bilateral = new QRadioButton(tr("bilateral"));
    gaussian = new QRadioButton(tr("gaussian"));

    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    tLay = new QVBoxLayout();// Layout herramientas

    tLay->addWidget(dpSigmaX);
    tLay->addWidget(slSigmaX);
    tLay->addWidget(dpSigmaY);
    tLay->addWidget(slSigmaY);
    tLay->addWidget(dpKSize);
    tLay->addWidget(slKSize);
    tLay->addWidget(box);
    tLay->addWidget(median);
    tLay->addWidget(bilateral);
    tLay->addWidget(gaussian);
    tLay->addWidget(applyB);
    tLay->addWidget(exitB);
    buttonG->setLayout(tLay);
    setLayout(tLay);
    gaussian->setChecked(true);
    viewSmooth(); // Empieza la funcion ver Suavizado
   // this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slSigmaX,SIGNAL(valueChanged(int)) , dpSigmaX , SLOT(display(int)));
    connect(slSigmaY,SIGNAL(valueChanged(int)) , dpSigmaY , SLOT(display(int)));
    connect(slKSize,SIGNAL(valueChanged(int)) , dpKSize , SLOT(display(int)));
    connect(slSigmaX,SIGNAL(valueChanged(int)) , this , SLOT(viewSmooth()));
    connect(slSigmaY,SIGNAL(valueChanged(int)) , this , SLOT(viewSmooth()));
    connect(slKSize,SIGNAL(valueChanged(int)) , this , SLOT(viewSmooth()));
    connect(box,SIGNAL(clicked()),this,SLOT(viewSmooth()));
    connect(median,SIGNAL(clicked()),this,SLOT(viewSmooth()));
    connect(bilateral,SIGNAL(clicked()),this,SLOT(viewSmooth()));
    connect(gaussian,SIGNAL(clicked()),this,SLOT(viewSmooth()));
}
/*void SmoothDialog::closeEvent(QCloseEvent *event){
    //event->ActionRemoved();
    event->accept();
    //imgL->setPixmap(QPixmap::fromImage(imgM));
}*/

SmoothDialog::~SmoothDialog(){
    imgL->setPixmap(QPixmap::fromImage(imgM.scaledToWidth(anch)));
}

void SmoothDialog::applyChanges(){

}

void SmoothDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

void SmoothDialog::viewSmooth(){

    src = QImage2Mat(imgM);
    cv::Mat dst;

    if(box->isChecked()){
        slSigmaX->setDisabled(true);
        slSigmaY->setDisabled(true);
        for ( int i = 1; i < slKSize->value(); i = i + 2 ){
            cv::boxFilter(src,dst,-1,cv::Size(i,i));
            src = dst;
        }
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(median->isChecked()){
        slSigmaX->setDisabled(true);
        slSigmaY->setDisabled(true);
        for ( int i = 1; i < slKSize->value(); i = i + 2 ){
            cv::medianBlur(src,dst,i);
            src = dst;
        }
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(bilateral->isChecked()){
        slSigmaX->setEnabled(true);
        slSigmaY->setEnabled(true);
        for ( int i = 1; i < slKSize->value(); i = i + 2 ){
            cv::bilateralFilter(src,dst,i,slSigmaX->value(),slSigmaY->value());
        }
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }
    else if(gaussian->isChecked()){
        slSigmaX->setEnabled(true);
        slSigmaY->setEnabled(true);
        for ( int i = 1; i < slKSize->value(); i = i + 2 ){
            cv::GaussianBlur( src, dst, cv::Size( i, i ),slSigmaX->value(), slSigmaY->value());
            src = dst;
        }
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
    }/*
    for(int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
           { blur( src, dst, Size( i, i ), Point(-1,-1) );
             if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

        /// Applying Gaussian blur
        if( display_caption( "Gaussian Blur" ) != 0 ) { return 0; }

        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
            { GaussianBlur( src, dst, Size( i, i ), 0, 0 );
              if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

         /// Applying Median blur
         if( display_caption( "Median Blur" ) != 0 ) { return 0; }

         for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
             { medianBlur ( src, dst, i );
               if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

         /// Applying Bilateral Filter
         if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }

         for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
             { bilateralFilter ( src, dst, i, i*2, i/2 );
               if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }*/
}

QImage SmoothDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat SmoothDialog::QImage2Mat(QImage const& src)

{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}
