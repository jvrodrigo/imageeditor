#include "filter2Ddialog.h"

Filter2DDialog::Filter2DDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    src = QImage2Mat(imgM);
    anch = parent->getAnch();   // Toma el ancho de la imagen

    //Radio buttons
    kernel3x3 = new QRadioButton("kernel 3x3");
    kernel5x5 = new QRadioButton("kernel 5x5");

    // Sliders
    slDelta = new QSlider(Qt::Horizontal) ;
    slDelta->setRange(0,1500);
    slDelta->setValue(0);
    slDelta->setToolTip("Sigma X");
    dpDelta = new QLCDNumber(3);
    dpDelta->display(0);

    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    // Kernel value
    n00 = new QSpinBox();
    n01 = new QSpinBox();
    n02 = new QSpinBox();
    n03 = new QSpinBox();
    n04 = new QSpinBox();
    n10 = new QSpinBox();
    n11 = new QSpinBox();
    n12 = new QSpinBox();
    n13 = new QSpinBox();
    n14 = new QSpinBox();
    n20 = new QSpinBox();
    n21 = new QSpinBox();
    n22 = new QSpinBox();
    n23 = new QSpinBox();
    n24 = new QSpinBox();
    n30 = new QSpinBox();
    n31 = new QSpinBox();
    n32 = new QSpinBox();
    n33 = new QSpinBox();
    n34 = new QSpinBox();
    n40 = new QSpinBox();
    n41 = new QSpinBox();
    n42 = new QSpinBox();
    n43 = new QSpinBox();
    n44 = new QSpinBox();

    n500 = new QSpinBox();
    n501 = new QSpinBox();
    n502 = new QSpinBox();
    n503 = new QSpinBox();
    n504 = new QSpinBox();
    n510 = new QSpinBox();
    n511 = new QSpinBox();
    n512 = new QSpinBox();
    n513 = new QSpinBox();
    n514 = new QSpinBox();
    n520 = new QSpinBox();
    n521 = new QSpinBox();
    n522 = new QSpinBox();
    n523 = new QSpinBox();
    n524 = new QSpinBox();
    n530 = new QSpinBox();
    n531 = new QSpinBox();
    n532 = new QSpinBox();
    n533 = new QSpinBox();
    n534 = new QSpinBox();
    n540 = new QSpinBox();
    n541 = new QSpinBox();
    n542 = new QSpinBox();
    n543 = new QSpinBox();
    n544 = new QSpinBox();

    n00->setMinimum(-10);
    n01->setMinimum(-10);
    n02->setMinimum(-10);
    n03->setMinimum(-10);
    n04->setMinimum(-10);
    n10->setMinimum(-10);
    n11->setMinimum(-10);
    n12->setMinimum(-10);
    n13->setMinimum(-10);
    n14->setMinimum(-10);
    n20->setMinimum(-10);
    n21->setMinimum(-10);
    n22->setMinimum(-10);
    n23->setMinimum(-10);
    n24->setMinimum(-10);
    n30->setMinimum(-10);
    n31->setMinimum(-10);
    n32->setMinimum(-10);
    n33->setMinimum(-10);
    n34->setMinimum(-10);
    n40->setMinimum(-10);
    n41->setMinimum(-10);
    n42->setMinimum(-10);
    n43->setMinimum(-10);
    n44->setMinimum(-10);

    n500->setMinimum(-10);
    n501->setMinimum(-10);
    n502->setMinimum(-10);
    n503->setMinimum(-10);
    n504->setMinimum(-10);
    n510->setMinimum(-10);
    n511->setMinimum(-10);
    n512->setMinimum(-10);
    n513->setMinimum(-10);
    n514->setMinimum(-10);
    n520->setMinimum(-10);
    n521->setMinimum(-10);
    n522->setMinimum(-10);
    n523->setMinimum(-10);
    n524->setMinimum(-10);
    n530->setMinimum(-10);
    n531->setMinimum(-10);
    n532->setMinimum(-10);
    n533->setMinimum(-10);
    n534->setMinimum(-10);
    n540->setMinimum(-10);
    n541->setMinimum(-10);
    n542->setMinimum(-10);
    n543->setMinimum(-10);
    n544->setMinimum(-10);

    x3LayPrin = new QVBoxLayout();
    x3Lay0 = new QHBoxLayout();
    x3Lay1 = new QHBoxLayout();
    x3Lay2 = new QHBoxLayout();

    x5LayPrin = new QVBoxLayout();
    x5Lay0 = new QHBoxLayout();
    x5Lay1 = new QHBoxLayout();
    x5Lay2 = new QHBoxLayout();
    x5Lay3 = new QHBoxLayout();
    x5Lay4 = new QHBoxLayout();

    x3Lay0->addWidget(n00);
    x3Lay0->addWidget(n01);
    x3Lay0->addWidget(n02);
    x3Lay1->addWidget(n10);
    x3Lay1->addWidget(n11);
    x3Lay1->addWidget(n12);
    x3Lay2->addWidget(n20);
    x3Lay2->addWidget(n21);
    x3Lay2->addWidget(n22);

    x5Lay0->addWidget(n500);
    x5Lay0->addWidget(n501);
    x5Lay0->addWidget(n502);
    x5Lay0->addWidget(n503);
    x5Lay0->addWidget(n504);
    x5Lay1->addWidget(n510);
    x5Lay1->addWidget(n511);
    x5Lay1->addWidget(n512);
    x5Lay1->addWidget(n513);
    x5Lay1->addWidget(n514);
    x5Lay2->addWidget(n520);
    x5Lay2->addWidget(n521);
    x5Lay2->addWidget(n522);
    x5Lay2->addWidget(n523);
    x5Lay2->addWidget(n524);
    x5Lay3->addWidget(n530);
    x5Lay3->addWidget(n531);
    x5Lay3->addWidget(n532);
    x5Lay3->addWidget(n533);
    x5Lay3->addWidget(n534);
    x5Lay4->addWidget(n540);
    x5Lay4->addWidget(n541);
    x5Lay4->addWidget(n542);
    x5Lay4->addWidget(n543);
    x5Lay4->addWidget(n544);

    tLay = new QVBoxLayout();// Layout herramientas
    layMatrix = new QVBoxLayout();
    widg3x3 = new QWidget();
    widg5x5 = new QWidget();
    tLay->addWidget(kernel3x3);// Radio button 3x3
    tLay->addWidget(kernel5x5);// Radio button 5x5

    x3LayPrin->addLayout(x3Lay0);
    x3LayPrin->addLayout(x3Lay1);
    x3LayPrin->addLayout(x3Lay2);

    x5LayPrin->addLayout(x5Lay0);
    x5LayPrin->addLayout(x5Lay1);
    x5LayPrin->addLayout(x5Lay2);
    x5LayPrin->addLayout(x5Lay3);
    x5LayPrin->addLayout(x5Lay4);


    layMatrix->addWidget(widg3x3);
    layMatrix->addWidget(widg5x5);
    tLay->addWidget(applyB);
    tLay->addWidget(exitB);
    tLay->addWidget(slDelta);
    tLay->addLayout(layMatrix);

    tLay->addWidget(dpDelta);

    kernel3x3->setChecked(true);
    widg3x3->setLayout(x3LayPrin);
    widg5x5->setLayout(x5LayPrin);
    widg5x5->hide();
    nMatrix = 3;
    setLayout(tLay);

    viewFilter();

    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slDelta,SIGNAL(valueChanged(int)) , dpDelta , SLOT(display(int)));
    connect(slDelta,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n00,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n01,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n02,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n10,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n11,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n12,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n20,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n21,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n22,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));

    connect(n500,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n501,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n502,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n503,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n504,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n510,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n511,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n512,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n513,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n514,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n520,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n521,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n522,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n523,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n524,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n530,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n531,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n532,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n533,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n534,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n540,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n541,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n542,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n543,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));
    connect(n544,SIGNAL(valueChanged(int)) , this , SLOT(viewFilter()));



    connect(kernel3x3,SIGNAL(clicked()) , this , SLOT(viewFilter()));
    connect(kernel5x5,SIGNAL(clicked()) , this , SLOT(viewFilter()));
}

Filter2DDialog::~Filter2DDialog(){

    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
}

void Filter2DDialog::applyChanges(){

}
void Filter2DDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

void Filter2DDialog::viewFilter(){
    if(kernel3x3->isChecked()){
        if(nMatrix!=3){
            widg3x3->show();
            widg5x5->hide();
        }
        cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                             n00->value(), n01->value(), n02->value(),
                             n10->value(), n11->value(), n12->value(),
                             n20->value(), n21->value(), n22->value());
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2YCrCb);
        cv::filter2D(dst,dst,-1,kernel,cv::Point(-1,-1),slDelta->value(),cv::BORDER_DEFAULT);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
        nMatrix=3;

    }else{
        if(nMatrix!=5){
            widg3x3->hide();
            widg5x5->show();

            //widg->setLayout(x5LayPrin);
            //layMatrix->removeWidget(widg);
            //layMatrix->addLayout(x5LayPrin);
        }
        cv::Mat kernel = (cv::Mat_<float>(5,5) <<
                            n500->value(), n501->value(), n502->value(),n503->value(),n504->value(),
                            n510->value(), n511->value(), n512->value(),n513->value(),n514->value(),
                            n520->value(), n521->value(), n522->value(),n523->value(),n524->value(),
                            n530->value(), n531->value(), n532->value(),n533->value(),n534->value(),
                            n540->value(), n541->value(), n542->value(),n543->value(),n544->value());
        cv::Mat dst;
        cv::cvtColor(src,dst,CV_RGB2YCrCb);
        cv::filter2D(dst,dst,-1,kernel,cv::Point(-1,-1),slDelta->value(),cv::BORDER_DEFAULT);
        imgL->setPixmap(QPixmap::fromImage(Mat2QImage(dst)).scaledToWidth(anch));
        nMatrix = 5;
    }

}

QImage Filter2DDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat Filter2DDialog::QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}
