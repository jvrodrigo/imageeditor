#include "blobsdialog.h"

BlobsDialog::BlobsDialog(ImgWin *parent) :
    QDialog(parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal
    anch = parent->getAnch();   // Toma el ancho de la imagen

    // Slider
    slthreshold = new QSlider(Qt::Horizontal) ;
    slthreshold->setRange(0,255);
    slthreshold->setValue(100);
    slthreshold->setToolTip("Threshold Blobs");
    disp = new QLCDNumber(4);
    disp->display(100);

    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    tLay = new QVBoxLayout();// Layout herramientas

    tLay->addWidget(disp);
    tLay->addWidget(slthreshold);

    tLay->addWidget(applyB);
    tLay->addWidget(exitB);

    setLayout(tLay);

    viewBlobs(); // Empieza la funcion ver Superficies

    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slthreshold,SIGNAL(valueChanged(int)) , disp , SLOT(display(int)));
    connect(slthreshold,SIGNAL(valueChanged(int)) , this,SLOT(viewBlobs()));
}

void BlobsDialog::applyChanges(){

}

void BlobsDialog::exit(){
    imgL->setPixmap(QPixmap::fromImage(imgM).scaledToWidth(anch));
    close();
}

void BlobsDialog::viewBlobs(){

    cv::Mat output = QImage2Mat(imgM);

    //cv::cvtColor(QImage2Mat(mImg),src,CV_RGB2HSV);
    cv::cvtColor(QImage2Mat(imgM),src,CV_RGB2GRAY);
    cv::Mat binary;

    cv::threshold(src, binary, slthreshold->value(), 1000, cv::THRESH_BINARY);
    FindBlobs(binary, blobs);

    // Randomy color the blobs
    for(size_t i=0; i < blobs.size(); i++) {
        unsigned char r = 255 * (rand()/(1.0 + RAND_MAX));
        unsigned char g = 255 * (rand()/(1.0 + RAND_MAX));
        unsigned char b = 255 * (rand()/(1.0 + RAND_MAX));

        for(size_t j=0; j < blobs[i].size(); j++) {
            int x = blobs[i][j].x;
            int y = blobs[i][j].y;

            output.at<cv::Vec3b>(y,x)[0] = b;
            output.at<cv::Vec3b>(y,x)[1] = g;
            output.at<cv::Vec3b>(y,x)[2] = r;
        }
    }
    imgL->setPixmap(QPixmap::fromImage(Mat2QImage(binary).scaledToWidth(anch)));
}
void BlobsDialog::FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs)
{
    blobs.clear();

    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    cv::Mat label_image;
    binary.convertTo(label_image, CV_32SC1);

    int label_count = 2; // starts at 2 because 0,1 are used already

    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 1) {
                continue;
            }
            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), label_count, &rect, 0, 0, 4);
            std::vector <cv::Point2i> blob;
            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point2i(j,i));
                }
            }
            blobs.push_back(blob);
            label_count++;
        }
    }
}

QImage BlobsDialog::Mat2QImage(cv::Mat const& src)
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

cv::Mat BlobsDialog::QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );

    return mat2;
}
