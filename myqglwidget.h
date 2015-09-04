#ifndef MYQGLWIDGET_H
#define MYQGLWIDGET_H
#include <QtWidgets>
#include <QGLWidget>
#include "imgwin.h"

QT_FORWARD_DECLARE_CLASS(QGLShaderProgram)

class MyQGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyQGLWidget(ImgWin *parent = 0, QGLWidget *shareWidget = 0);
    ~MyQGLWidget();
    QImage      imgM;
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void rotateBy(int xAngle, int yAngle, int zAngle);
    void setClearColor(const QColor &color);

signals:
    void clicked();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void makeObject();

    QColor clearColor;
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;
    GLuint textures[6];
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
#ifdef QT_OPENGL_ES_2
    QGLShaderProgram *program;
#endif
};
#endif
/*



#include    <gl\gl.h>                         // Header File For The OpenGL32 Library
#include    <gl\glu.h>                            // Header File For The GLu32 Library
#include    <gl\glaux.h>                          // Header File For The GLaux Library
#include    <QGLWidget>
#include    "imgwin.h"

class MyQGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    MyQGLWidget(ImgWin *parent = 0);
    AUX_RGBImageRec *imagen[1];
    static std::wstring s2ws(const std::string& s);
    LPCWSTR *LoadBMP(char* Filename);
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();

};

#endif // MYQGLWIDGET_H
*/
