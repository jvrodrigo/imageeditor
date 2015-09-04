#include "qimagecv.h"

#include <QDebug>

//----------------------------------

QImageCV::QImageCV () : QImage()	
{	
colorSys << "RGB" << "XYZ" << "LUV" << "LAB" << "YUV" << "HSV"  <<  "YCC" ;
}

//----------------------------------

QImageCV::QImageCV ( const QSize & size, Format fmt ) : QImage (size,fmt)
{
matI = cv::Mat::zeros ( size.height() , size.width() , CV_8UC3 ) ;
matC = cv::Mat::zeros ( size.height() , size.width() , CV_8UC1 ) ;
colorSys << "RGB" << "XYZ" << "LUV" << "LAB" << "YUV" << "HSV"  <<  "YCC" ;
}

//----------------------------------

QImageCV::QImageCV ( const QString & fNam, const char * fmt ) : QImage (fNam,fmt)
{
cv::Mat mat = cv::Mat (height(),width(),CV_8UC4,(uchar*)bits(),bytesPerLine());
matI = cv::Mat ( mat.rows , mat.cols , CV_8UC3 );
matC = cv::Mat ( mat.rows , mat.cols , CV_8UC1 );
cv::Mat ocvI[] = { matI , matC } ;
int from_to[] = { 0 , 0 , 1 , 1 , 2 , 2  , 3 , 3 };
cv::mixChannels( &mat, 1, ocvI, 2, from_to , 4 );	
mat.release();
colorSys << "RGB" << "XYZ" << "LUV" << "LAB" << "YUV" << "HSV"  <<  "YCC" ;
}

//----------------------------------

QImageCV::QImageCV ( QImage img ) : QImage (img)
{
cv::Mat mat = cv::Mat (height(),width(),CV_8UC4,(uchar*)bits(),bytesPerLine());
matI = cv::Mat ( mat.rows , mat.cols , CV_8UC3 );
matC = cv::Mat ( mat.rows , mat.cols , CV_8UC1 );
cv::Mat ocvI[] = { matI , matC } ;
int from_to[] = { 0 , 0 , 1 , 1 , 2 , 2  , 3 , 3 };
cv::mixChannels( &mat, 1, ocvI, 2, from_to , 4 );	
mat.release();
colorSys << "RGB" << "XYZ" << "LUV" << "LAB" << "YUV" << "HSV"  <<  "YCC" ;
}

//----------------------------------

QImageCV::QImageCV ( const cv::Mat &frm )
{
QImage img ;
QImage::Format val ;

const uchar *qIB = frm.ptr() ;
if	( frm.channels() > 1 )      val = QImage::Format_RGB888 ;
    //img = QImage (qIB,frm.cols,frm.rows,frm.step,QImage::Format_RGB888) ;
else                            val = QImage::Format_Indexed8 ;
    //img = QImage (qIB,frm.cols,frm.rows,frm.step,QImage::Format_Indexed8) ;
    
img = QImage (qIB,frm.cols,frm.rows,frm.step,val) ;
*this = (img.convertToFormat (QImage::Format_ARGB32,Qt::AutoColor)).rgbSwapped()  ;
matC = cv::Mat::zeros ( frm.rows , frm.cols , CV_8UC1 ) ;
matI = cv::Mat(frm);
colorSys << "RGB" << "XYZ" << "LUV" << "LAB" << "YUV" << "HSV"  <<  "YCC" ;
}

//----------------------------------

QImageCV::~QImageCV ()		
{	
matI.release();		
matC.release();			
colorSys.clear();	
}

//----------------------------------

void	QImageCV::setImage ( QImage *pImg )
{
*this = pImg->copy() ;
}

//----------------------------------

cv::Mat&        QImageCV::getcvMat			( void )            
{ 
qDebug() << "dentro" << matI.cols << matI.rows ;
return matI ; 
}

//----------------------------------


QString		QImageCV::getColorSystem		( int chn )
{
QString	answ ;
switch	( chn)
		{
		case	RGB	:	answ.append("(RGB)") ;			break ;
		case	RRGB	:	answ.append("R - (RGB)") ;		break ;
		case	GRGB	:	answ.append("G - (RGB)") ;		break ;
		case	BRGB	:	answ.append("B - (RGB)") ;		break ;
		case	XYZ	:	answ.append("(XYZ)") ;			break ;
		case	XXYZ	:	answ.append("X - (XYZ)") ;		break ;
		case	YXYZ	:	answ.append("Y - (XYZ)") ;		break ;
		case	ZXYZ	:	answ.append("Z - (XYZ)") ;		break ;
		case	LUV	:	answ.append("(LUV)") ;			break ;
		case	LLUV	:	answ.append("L - (LUV)") ;		break ;
		case	ULUV	:	answ.append("U - (LUV)") ;		break ;
		case	VLUV	:	answ.append("V - (LUV)") ;		break ;
		case	LAB	:	answ.append("(LAB)") ;			break ;
		case	LLAB	:	answ.append("L - (LAB)") ;		break ;
		case	ALAB	:	answ.append("A - (LAB)") ;		break ;
		case	BLAB	:	answ.append("B - (LAB)") ;		break ;
		case	YUV	:	answ.append("(YUV)") ;			break ;
		case	YYUV	:	answ.append("Y - (YUV)") ;		break ;
		case	UYUV	:	answ.append("U - (YUV)") ;		break ;
		case	VYUV	:	answ.append("V - (YUV)") ;		break ;
		case	HSV	:	answ.append("(HSV)") ;			break ;
		case	HHSV	:	answ.append("H - (HSV)") ;		break ;
		case	SHSV	:	answ.append("S - (HSV)") ;		break ;
		case	VHSV	:	answ.append("V - (HSV)") ;		break ;
		case	YCC	:	answ.append("(YCC)") ;			break ;
		case	YYCC	:	answ.append("Y - (YCC)") ;		break ;
		case	CRYCC	:	answ.append("Cr - (YCC)") ;		break ;
		case	CBYCC	:	answ.append("Cb - (YCC)") ;		break ;
		default :	answ.append("(---)") ; break ;
		}
return answ ;
}

//----------------------------------

QImage		QImageCV::getChannel ( int  chn )
{
QImage		result ;
const uchar	*qIB ;
if	( chn < 1 )	return getQImage() ;
cv::Mat		frm = cv::Mat ( matI.rows , matI.cols , CV_8UC3 );
cv::Mat		chn1 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		chn2 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		chn3 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		ocvI[] = { chn1 , chn2 , chn3 } ;
int fto[] = { 0 , 2 , 1 , 1 , 2 , 0  , 3 , 3 };
int				syscor , cor ;

syscor	= ( chn / 10 ) * 10 ;
cor = chn - syscor ;
switch	( syscor)
    {
    case RGB : cv::mixChannels ( &matI , 1, &frm , 1, fto , 3 );     break ;
    case XYZ : cv::cvtColor ( matI , frm , CV_BGR2XYZ , 0 ) ;		break ;
    case LUV : cv::cvtColor ( matI , frm , CV_BGR2Luv , 0 ) ;		break ;
    case LAB : cv::cvtColor ( matI , frm , CV_BGR2Lab , 0 ) ;		break ;
    case YUV : colorMine ( matI , frm , CM_RGB2YUV ) ;				break ;
    case HSV : cv::cvtColor ( matI , frm , CV_BGR2HSV , 0 ) ;		break ;
    case YCC : cv::cvtColor ( matI , frm , CV_BGR2YCrCb , 0 ) ;		break ;
    default  : cv::cvtColor ( matI , frm , CV_RGB2GRAY , 0 ) ;		break ;
    }
cv::split (frm,ocvI) ;
switch	( cor )
    {
    default :
    case 1 : qIB = chn1.ptr() ;		matC = chn1 ;       break ;
    case 2 : qIB = chn2.ptr() ;		matC = chn2 ;       break ;
    case 3 : qIB = chn3.ptr() ;		matC = chn3 ;       break ;
    }
result = QImage(qIB,frm.cols,frm.rows,frm.step/3,QImage::Format_Indexed8) ;
frm.release();		chn1.release();		chn2.release();		chn3.release();
return result.convertToFormat (QImage::Format_ARGB32,Qt::AutoColor) ;
}

//----------------------------------

cv::Mat&		QImageCV::getChannelMat		( int chn )
{
cv::Mat		frm = cv::Mat ( matI.rows , matI.cols , CV_8UC3 );
cv::Mat		chn1 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		chn2 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		chn3 = cv::Mat ( matI.rows , matI.cols , CV_8UC1 );
cv::Mat		ocvI[] = { chn1 , chn2 , chn3 } ;
int				syscor , cor ;

syscor	= ( chn / 10 ) * 10 ;
cor = chn - syscor ;

switch	( syscor)
    {
    case RGB : frm = cv::Mat(matI);                                 break ;
    case XYZ : cv::cvtColor ( matI , frm , CV_BGR2XYZ , 0 ) ;		break ;
    case LUV : cv::cvtColor ( matI , frm , CV_BGR2Luv , 0 ) ;		break ;
    case LAB : cv::cvtColor ( matI , frm , CV_BGR2Lab , 0 ) ;		break ;
    case YUV : colorMine ( matI , frm , CM_RGB2YUV ) ;				break ;
    case HSV : cv::cvtColor ( matI , frm , CV_BGR2HSV , 0 ) ;		break ;
    case YCC : cv::cvtColor ( matI , frm , CV_BGR2YCrCb , 0 ) ;		break ;
    default  : cv::cvtColor ( matI , frm , CV_RGB2GRAY , 0 ) ;		break ;
    }
cv::split (frm,ocvI) ;
switch	( cor )
    {
    case 1	: matC = chn1 ;			break ;
    case 2	: matC = chn2 ;			break ;
    case 3	: matC = chn3 ;			break ;
    default	: matC = cv::Mat::ones (matI.rows , matI.cols , CV_8UC1 );	break ;
    }
frm.release();		chn1.release();		chn2.release();		chn3.release();
return matC ;
}

//----------------------------------

bool    QImageCV::colorMine (cv::Mat &input , cv::Mat &output , int modeCS )
{
uchar       *ptrI  , *ptrO , ci1 , ci2 , ci3 ;
qreal       cr1 , cr2 , cr3 ;
int         ncol , nrow ;
bool        status ;

input.copyTo(output) ;
status = input.isContinuous() && ( input.type() == CV_8UC3 ) ;
status = status && ( input.channels() > 2 ) ;
status = status && ( input.rows > 0 ) && ( input.cols > 0 )  ;
if	( !status )	return false ;
switch ( modeCS )
	{
	case CM_RGB2ACC :
        for	(nrow=0; nrow<input.rows; nrow++)
            {
            ptrI = input.ptr(nrow) ;		ptrO = output.ptr(nrow) ;
            for	( ncol=0; ncol<input.cols; ncol++)
            	{
            	cr1=*(ptrI++)/255.0;    
            	cr2=*(ptrI++)/255.0;     
            	cr3=*(ptrI++)/255.0 ;
            	*(ptrO++) = (uchar) ( 85 * ( 2*cr3 + cr2) ) ;
            	*(ptrO++) = (uchar) ( 127.5 * (cr3 - cr2 + 1 ) ) ;
            	*(ptrO++) = (uchar) ( 63.75 * (cr3 + cr2 - 2*cr1 + 2 ) ) ;
            	}
            }
        break ;
    case CM_RGB2YUV :
        for	( nrow=0; nrow<input.rows; nrow++ )
        	{
        	ptrI = input.ptr(nrow) ;		ptrO = output.ptr(nrow) ;
        	for	( ncol=0; ncol<input.cols; ncol++)
        		{
        		ci1 = *(ptrI++) ;		ci2=*(ptrI++) ;		ci3 = *(ptrI++) ;
        		cr1 = 0.299*ci3 + 0.587*ci2 + 0.114*ci1 ;
        		*(ptrO++) = (uchar) ( cr1 ) ;
        		*(ptrO++) = (uchar) ( 0.493*(ci1-cr1) ) + 127 ;
        		*(ptrO++) = (uchar) ( 0.877*(ci3-cr1) ) + 127 ;
        		}
        	}
        break ;
    case CM_RGB2LMS :
    	for	( nrow=0; nrow<input.rows; nrow++ )
    		{
    		ptrI = input.ptr(nrow) ;		ptrO = output.ptr(nrow) ;
    		for	( ncol=0; ncol<input.cols; ncol++)
    			{
    			ci1 = *(ptrI++) ;		ci2=*(ptrI++) ;		ci3 = *(ptrI++) ;
    			cr1 = 0.3811*ci3 + 0.5783*ci2 + 0.0402*ci1 ;
    			cr2 = 0.1967*ci3 + 0.7244*ci2 + 0.0782*ci1 ;
    			cr3 = 0.0241*ci3 + 0.1288*ci2 + 0.8444*ci1 ;
    			*(ptrO++) = (uchar) ( cr1 ) ;
    			*(ptrO++) = (uchar) ( cr2 ) ;
    			*(ptrO++) = (uchar) ( cr3 ) ;
    			}
    		}
    	break ;
    default: break ;
    }
return true ;
}


//----------------------------------
