#include "mainwindow.h"
#include "channelcolordialog.h"
#include "histogramsdialog.h"
#include "cannydialog.h"
#include "blobsdialog.h"
#include "edgesdialog.h"
#include "smoothdialog.h"
#include "gammadialog.h"
#include "filter2Ddialog.h"
#include "qglwidgetdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon(DEFAULT_ICON_FILE));
    //Botones
    openB = new QPushButton("Open");
    saveB = new QPushButton("Save");
    exitB = new QPushButton("Exit");

    openB->setIcon(QIcon(QPixmap(DEFAULT_ICON_OPEN)));
    saveB->setIcon(QIcon(QPixmap(DEFAULT_ICON_SAVE)));
    exitB->setIcon(QIcon(QPixmap(DEFAULT_ICON_EXIT)));

    qglWidgetB = new QPushButton("QGLWidget");
    channelB = new QPushButton("Canales");
    histogramsB = new QPushButton("Histogramas");
    edgesB = new QPushButton("Bordes");
    cannyB = new QPushButton("Canny");
    blobsB = new QPushButton("Superficies");
    smoothB = new QPushButton("Suavizado");
    gammaB = new QPushButton("Gamma");
    filter2DB = new QPushButton("Filtro 2D");

    // Indicador y slider tamaño de la Imagen

    dpSize = new QLCDNumber(4);
    dpSize->display(100);
    slSize = new QSlider(Qt::Horizontal);
    slSize->setRange(1,300);
    slSize->setValue(100);
    slSize->setToolTip("Zoom");

    // Layout y widgets
    mWid = new QWidget();// Widget principal central
    layPrin = new QVBoxLayout(); // Layout Principal
    layFile = new QHBoxLayout(); // Layout File
    layQGLWidget = new QHBoxLayout(); // Layout QGLWidget
    layFilters = new QHBoxLayout(); // Layout contenedor de los filtros
    laySize = new QVBoxLayout(); // Layout Principal
    layF1 = new QVBoxLayout(); // Layout 1 Filters
    layF2 = new QVBoxLayout(); // Layout 1 Filters
    layFile->addWidget(openB);         // Boton abrir imagen
    layFile->addWidget(saveB);         // Boton guardar imagen
    layFile->addWidget(exitB);         // Boton cerrar imagen

    laySize->addWidget(slSize);       // Slider tamaño
    laySize->addWidget(dpSize);       // LCD indicador*/

    layQGLWidget->addWidget(qglWidgetB);      // Boton QGLWidget
    layF1->addWidget(channelB);      // Boton Canales
    layF1->addWidget(histogramsB);      // Boton Histogramas
    layF1->addWidget(smoothB);        // Boton suavizado
    layF1->addWidget(edgesB);  // Boton detectar bordes Roberts, Prewit, Sobel, Scharr, laplaciana y LOG
    layF2->addWidget(blobsB);  // Boton detectar superficies
    layF2->addWidget(cannyB);  // Boton filtro canny
    layF2->addWidget(gammaB);  // Boton Gamma
    layF2->addWidget(filter2DB);  // Boton Filtro 2D

    layFilters->addLayout(layF1);
    layFilters->addLayout(layF2);

    layPrin->addLayout(layFile); // Añade el layout File
    layPrin->addSpacing(10);
    layPrin->addLayout(layQGLWidget); // Añade el layout File
    layPrin->addSpacing(10);
    layPrin->addLayout(layFilters); // Añade el layout filtros
    layPrin->addSpacing(10);
    layPrin->addLayout(laySize);

    mWid->setLayout(layPrin);
    setCentralWidget(mWid);
    imgW = new ImgWin(this); // Ventana Principal de la Imagen

    // Signals and slots
    connect(openB,SIGNAL(clicked()),imgW,SLOT(openFile())) ;
    connect(saveB,SIGNAL(clicked()),imgW,SLOT(saveFile())) ;
    connect(exitB,SIGNAL(clicked()),this,SLOT(close())) ;
    connect(slSize,SIGNAL(valueChanged(int)),imgW,SLOT(scaleImage(int))) ;
    connect(slSize,SIGNAL(valueChanged(int)),dpSize,SLOT(display(int))) ;
    // Conectores de los filtros
    connect(cannyB,SIGNAL(clicked()), this , SLOT(startCannyDialog()));
    connect(blobsB,SIGNAL(clicked()), this , SLOT(startBlobsDialog()));
    connect(edgesB,SIGNAL(clicked()), this , SLOT(startEdgesDialog()));
    connect(channelB,SIGNAL(clicked()), this , SLOT(startChannelColorDialog()));
    connect(histogramsB,SIGNAL(clicked()), this , SLOT(startHistogramsDialog()));
    connect(smoothB,SIGNAL(clicked()), this , SLOT(startSmoothDialog()));
    connect(gammaB,SIGNAL(clicked()), this , SLOT(startGammaDialog()));
    connect(filter2DB,SIGNAL(clicked()), this , SLOT(startFilter2DDialog()));
    connect(qglWidgetB,SIGNAL(clicked()), this , SLOT(startQGLWidgetDialog()));
}

void MainWindow::startQGLWidgetDialog(){

    QGLWidgetDialog *start = new QGLWidgetDialog(imgW);
    start->setWindowTitle("QGLWidget");
    start->setModal(true);
    start->exec();
}

void MainWindow::startFilter2DDialog(){
    Filter2DDialog *start = new Filter2DDialog(imgW);
    start->setWindowTitle("Filtro 2D");
    start->setModal(true);
    start->exec();
}

void MainWindow::startGammaDialog(){
    GammaDialog *start = new GammaDialog(imgW);
    start->setWindowTitle("Gamma");
    start->setModal(true);
    start->exec();
}

void MainWindow::startSmoothDialog(){
    SmoothDialog *start = new SmoothDialog(imgW);
    start->setWindowTitle("Suavizado");
    start->setModal(true);
    start->exec();
}
void MainWindow::startHistogramsDialog(){
    HistogramsDialog *start = new HistogramsDialog(imgW);
    start->setWindowTitle("Histogramas");
    start->setModal(true);
    start->exec();
}
void MainWindow::startChannelColorDialog(){
    ChannelColorDialog *start = new ChannelColorDialog(imgW);
    start->setWindowTitle("Canales");
    start->setModal(true);
    start->exec();
}
void MainWindow::startEdgesDialog(){
    EdgesDialog *start = new EdgesDialog(imgW);
    start->setWindowTitle("Bordes");
    start->setModal(true);
    start->exec();
}
void MainWindow::startCannyDialog(){
    CannyDialog *start = new CannyDialog(imgW);
    start->setWindowTitle("Canny");
    start->setModal(true);
    start->exec();
}
void MainWindow::startBlobsDialog(){
    BlobsDialog *start = new BlobsDialog(imgW);
    start->setWindowTitle("Superficies");
    start->setModal(true);
    start->exec();
}
MainWindow::~MainWindow()
{

}

