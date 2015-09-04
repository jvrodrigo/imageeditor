#include "qglwidgetdialog.h"

QGLWidgetDialog::QGLWidgetDialog(ImgWin *parent)
{
    imgM = parent->getMImg(); // Obtiene la imagen QImage Principal
    imgL = parent->getLabelImg(); // Obtiene el label de la QImage Principal

    // Slider
    slZ = new QSlider(Qt::Horizontal) ;
    slZ->setRange(0,255);
    slZ->setValue(100);
    slZ->setToolTip("Profundidad");
    dpZ = new QLCDNumber(4);
    dpZ->display(100);

    myQGLWidget = new MyQGLWidget(parent);

    //Botones
    applyB = new QPushButton("Aplicar");
    exitB = new QPushButton("Salir");

    tLay = new QVBoxLayout();// Layout herramientas
    //tLay->addWidget(myQGLWidget);
    tLay->addWidget(myQGLWidget);
    tLay->addWidget(dpZ);
    tLay->addWidget(slZ);

    tLay->addWidget(applyB);
    tLay->addWidget(exitB);

    setLayout(tLay);

    viewQGLWidget(); // Empieza el filtro

    connect(exitB,SIGNAL(clicked()) ,this,SLOT(exit()));
    connect(applyB,SIGNAL(clicked()) ,this,SLOT(applyChanges()));
    connect(slZ,SIGNAL(valueChanged(int)) , dpZ , SLOT(display(int)));
    connect(slZ,SIGNAL(valueChanged(int)) , this,SLOT(viewQGLWidget()));
}

void QGLWidgetDialog::viewQGLWidget(){

}

void QGLWidgetDialog::applyChanges(){

}

void QGLWidgetDialog::exit(){
   // imgL->setPixmap(QPixmap::fromImage(imgM));
    close();
}

