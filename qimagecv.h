#ifndef QImageCV_H
#define QImageCV_H

#include <QImage>
#include <QVector>
#include <QStringList>

#ifndef OPENCVCORE
	#define OPENCVCORE
        #include "opencv2/core/core.hpp"
#endif
#ifndef OPENCVHIGHGUI
	#define OPENCVHIGHGUI
        #include "opencv2/highgui/highgui.hpp"
#endif
#ifndef OPENCVPROC
	#define OPENCVPROC
        #include "opencv2/imgproc/imgproc.hpp"
#endif


#ifndef CHROMACHAN
	#define	CHROMACHAN		9999
	#define	RGB             0
	#define	RRGB            1
	#define	GRGB            2
	#define	BRGB            3
	#define	XYZ             10
	#define	XXYZ            11
	#define	YXYZ            12
	#define	ZXYZ            13
	#define	LUV             20
	#define	LLUV            21
	#define	ULUV            22
	#define	VLUV            23
	#define	LAB             30
	#define	LLAB            31
	#define	ALAB            32
	#define	BLAB            33
	#define	YUV             40
	#define	YYUV            41
	#define	UYUV            42
	#define	VYUV            43
	#define	HSV             50
	#define	HHSV            51
	#define	SHSV            52
	#define	VHSV            53
    #define	YCC             70
	#define	YYCC            71
	#define	CRYCC           72
	#define	CBYCC           73
	#define	CM_RGB2ACC		6483
	#define	CM_RGB2YUV		6484
	#define	CM_RGB2LMS		6485
#endif

class QImageCV :public QImage
{
public:

QImageCV () ;
QImageCV ( const QSize & size, Format fmt ) ;
QImageCV ( const QString &fNam, const char * fmt=0 ) ;
QImageCV ( QImage img ) ;
QImageCV ( const cv::Mat &frm ) ;
~QImageCV ();
cv::Mat&        getcvMat			( void )  ;
QImage          getQImage           ( void )            { return this->copy() ; }
QImage          cvtColorLUV     	( void ) ;
QImage          getChannel      	( int chn ) ;
cv::Mat&        getChannelMat   	( int chn ) ;
QString         getColorSystem  	( int chn ) ;
QStringList&	getColorSystemList	( void )            { return colorSys ;	}

public slots :

void			setImage        ( QImage *pImg ) ;
bool			colorMine       ( cv::Mat &input , cv::Mat &output , int modeCS ) ;

private :
cv::Mat		matI , matC ;
QStringList	colorSys ;
};

#endif // QImageCVCV_H
