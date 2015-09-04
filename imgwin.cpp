#include "imgwin.h"
#include <QFileDialog>
ImgWin::ImgWin(QWidget *parent) :
    QMainWindow(parent)
{
    widg = new QWidget();
    imgL = new QLabel();

    mImg.load(DEFAULT_IMG_FILE); // Carga la imagen del disco
    fname = DEFAULT_IMG_FILE;

    anch = mImg.width();// Obtiene el ancho de la imagen
    imgLay = new QVBoxLayout();
    statusBar = new QStatusBar(); // Barra de estado inferior
    statusLabel = new QLabel(this); // Label de la barra de estado
    statusLabel->setText(QFileInfo(fname).absolutePath() +"/"+ QFileInfo(fname).fileName());
    statusBar->addPermanentWidget(statusLabel);

    // Carga la imagen en el layout QLabel imgL
    imgL->setPixmap(QPixmap::fromImage(mImg));// Pixmap de la imagen
    imgLay->addWidget(imgL);//Añade el layout del pixmap imagen
    imgLay->addWidget(statusBar);
    widg->setLayout(imgLay); // Layout del widget
    setCentralWidget(widg); // Centra el widget

    show();
}

void ImgWin::openFile()
{
    fname = QFileDialog::getOpenFileName(this,"Open Image",DEFAULT_IMAGE_PATH,
                                         "Images (*.png *.jpg)") ;
    if ( fname.isEmpty() ) return ;
    mImg.load(fname);
    anch = mImg.width();// Obtiene el ancho de la imagen

    imgL->setPixmap(QPixmap::fromImage(mImg).scaledToWidth(mImg.width()));
    this->resize(this->sizeHint());//mImg.size());
    setWindowIcon(QIcon(fname));

    statusLabel->setText(QFileInfo(fname).absolutePath() +"/"+ QFileInfo(fname).fileName());// Actualiza el status bar Path de la imagen
}

void ImgWin::saveFile()
{
    fname = QFileDialog::getSaveFileName(this,"Save Image",fname,"Images (*.png *.jpg)") ;
    if ( fname.isEmpty() ) return ;
    mImg.save(fname) ;
}

QImage ImgWin::getMImg(){
    return mImg;
}
QLabel * ImgWin::getLabelImg(){
    return imgL;
}
void ImgWin::setLabelImg(QLabel *label){
    imgL = label;
}
int ImgWin::getAnch(){
    return this->anch;
}

QString ImgWin::getFileName(){
    return fname;
}

void ImgWin::scaleImage(int anch)
{
    this->anch = (mImg.width()*anch)/100;
    imgL->setPixmap(QPixmap::fromImage(mImg.scaledToWidth(this->anch)));
    this->resize(this->sizeHint());
}

