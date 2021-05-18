#pragma once
#pragma comment (lib, "opengl32.lib")

#include <QtWidgets/QWidget>
#include "ui_View.h"
#include <qopenglwindow.h>
#include <QOpenGLWidget>
#include <QGLWidget>
#include <QDebug>
#include <QKeyEvent>
#include "Data.h"

class View : public QOpenGLWidget
{
    Q_OBJECT
protected:
        Data data;
        enum { VIZUALIZATION_QUADS, VIZUALIZATION_QUADSTRIP, VIZUALIZATION_TEXTURE } vizualization_state;
        enum {XY, YZ, XZ} axes;
        int layer;
        GLuint VBOtexture; //номер текстуры в памяти видеокарты
        QImage textureImage;
public:
    View(QOpenGLWidget *parent = Q_NULLPTR);
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    int TransferFunction(short value);
    void VizualizationQuads();
    void VizualizationQuadStrip();
    void VizualizationTexture(); //риссует прямоугольник с наложенной текстурой
    void keyPressEvent(QKeyEvent* event);
    void Load2dTexture();
    void genTextureImage(); //генерация изображения из томограммы
    void LoadData(string fn);

private:
    Ui::ViewClass ui;
};
