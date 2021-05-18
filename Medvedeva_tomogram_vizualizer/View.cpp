#include "View.h"

View::View(QOpenGLWidget *parent)
    : QOpenGLWidget(parent)
{
    ui.setupUi(this);
}

//инициализация
void View::initializeGL()
{
    glClearColor(Qt::white, Qt::white, Qt::white, Qt::white); //заполняющий цвет  
    glShadeModel(GL_SMOOTH); //режим сглаживания
    glMatrixMode(GL_MODELVIEW); //модельно-видовая матрица
    glLoadIdentity(); //загрузка единичной матрицы
    glGenTextures(1, &VBOtexture); //генерация уникального номера текстуры
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //наложение текстуры, цвет которой перекрывает цвет пикселя
}

//изменение размеров окна
void View::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION); //режим матрицы
    glLoadIdentity(); //загрузка единичной матрицы
    glOrtho(0.0f, data.getWidth() - 1, 0.0f, data.getHeight() - 1, -1.0f, 1.0f); //установка ортогонального преобразования
    glViewport(0, 0, nWidth, nHeight); //установка окна обзора
    update();
}

int View::TransferFunction(short value)
{
    float c = (value - data.getMin()) * 255 / (data.getMax() - data.getMin());
  //  return QColor(c, c, c);
    return c;
}

void View::VizualizationQuads()
{
    int c;
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();

    switch (axes)
    {
    case XY:
        for (int y = 0; y < h - 1; y++)
        {
            for (int x = 0; x < w - 1; x++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[layer * w * h + y * w + x]);
                glColor3i(c, c, c);
                glVertex2i(x, y);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + x]);
                glColor3i(c, c, c);
                glVertex2i(x, y + 1);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + (x + 1)]);
                glColor3i(c, c, c);
                glVertex2i(x + 1, y + 1);

                c = TransferFunction(data[layer * w * h + y * w + (x + 1)]);
                glColor3i(c, c, c);
                glVertex2i(x + 1, y);

                glEnd();
            }
        }
        break;

    case XZ:
       /* for (int x = 0; x < w - 1; x++)
        {
            for (int z = 0; z < d - 1; z++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[layer * w * h + x * w + z]);
                glColor3i(c, c, c);
                glVertex2i(z, x);

                c = TransferFunction(data[layer * w * h + (x + 1) * w + z]);
                glColor3i(c, c, c);
                glVertex2i(z, x + 1);

                c = TransferFunction(data[layer * w * h + (x + 1) * w + (z + 1)]);
                glColor3i(c, c, c);
                glVertex2i(z + 1, x + 1);

                c = TransferFunction(data[layer * w * h + x * w + (z + 1)]);
                glColor3i(c, c, c);
                glVertex2i(z + 1, x);

                glEnd();
            }
        }*/
        for (int z = 0; z < d - 1; z++)
        {
            for (int x = 0; x < w - 1; x++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[z*h*w + layer * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, z);

                c = TransferFunction(data[(z+1) * h * w + layer * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, z+1);

                c = TransferFunction(data[(z+1) * h * w + layer * w + (x+1)]);
                glColor3f(c, c, c);
                glVertex2i(x+1, z+1);

                c = TransferFunction(data[z * h * w + layer * w + (x+1)]);
                glColor3f(c, c, c);
                glVertex2i(x+1, z);

                glEnd();
            }
        }
        break;
        
    case YZ:
       /* for (int y = 0; y < h - 1; y++)
        {
            for (int z = 0; z < d - 1; z++)
            {
                glBegin(GL_QUADS);

                c = TransferFunction(data[layer * w * h + y * w + z]);
                glColor3i(c, c, c);
                glVertex2i(z, y);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + z]);
                glColor3i(c, c, c);
                glVertex2i(z, y + 1);

                c = TransferFunction(data[layer * w * h + (y + 1) * w + (z + 1)]);
                glColor3i(c, c, c);
                glVertex2i(z + 1, y + 1);

                c = TransferFunction(data[layer * w * h + y * w + (z + 1)]);
                glColor3i(c, c, c);
                glVertex2i(z + 1, y);

                glEnd();
            }
        }*/
        for (int y = 0; y < h - 1; y++)
        {
            for (int z = 0; z < d - 1; z++)
            {
                glBegin(GL_QUADS);
                c = TransferFunction(data[z * w * h + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z, y);

                c = TransferFunction(data[z * w * h + (y+1) * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z, y+1);

                c = TransferFunction(data[(z+1) * w * h + (y+1) * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z+1, y+1);

                c = TransferFunction(data[(z+1) * w * h + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(z+1, y);

                glEnd();
            }
        }
        break;
    }
 }

void View::VizualizationQuadStrip()
{
    int c;
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();


    switch (axes)
    {
    case XY:
        for (int y = 0; y < h - 1; y++)
        {
            glBegin(GL_QUAD_STRIP);
            for (int x = 0; x < w - 1; x++)
            {
                c = TransferFunction(data[layer * h * w + y * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, y);

                c = TransferFunction(data[layer * h * w + (y + 1) * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, y + 1);
            }
            glEnd();
        }
        break;
        /*
        * for (int x=0; x < w - 1; y++)
        {
            glBegin(GL_QUAD_STRIP);
            for (int y = 0; y < h - 1; y++)
            {
                c = TransferFunction(data[layer * h * w + x*h + y]);
                glColor3i(c, c, c);
                glVertex2i(x, y);

                c = TransferFunction(data[layer * h * w + (x+1) * h + y]);
                glColor3i(c, c, c);
                glVertex2i(x+1, y);
            }
            glEnd();
        }
        break;
        */

    case XZ:
    {
        for (int z = 0; z < d - 1; z++)
        {
            glBegin(GL_QUAD_STRIP);
            for (int x = 0; x < w - 1; x++)
            {
                c = TransferFunction(data[z * h * w + layer * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, z);

                c = TransferFunction(data[(z+1) * h * w + layer * w + x]);
                glColor3f(c, c, c);
                glVertex2i(x, z+1);
            }
            glEnd();
        }
        break;
    }

    case YZ:
    {
        for (int z = 0; z < d - 1; z++)
        {
            glBegin(GL_QUAD_STRIP);
            for (int y = 0; y < h - 1; y++)
            {
                c = TransferFunction(data[z * w * h + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(y,z);

                c = TransferFunction(data[(z+1) * w * h + y * w + layer]);
                glColor3f(c, c, c);
                glVertex2i(y, z+1);
            }
            glEnd();
        }
        break;
    }
    }
}

void View::VizualizationTexture()
{
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i(0, 0);
    glTexCoord2f(0, 1);
    glVertex2i(0, data.getHeight());
    glTexCoord2f(1,1);
    glVertex2i(data.getWidth(), data.getHeight());
    glTexCoord2f(1, 0);
    glVertex2i(data.getWidth(), 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//визуализация
void View::paintGL()
{
    qDebug() << "repaint" << vizualization_state; 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (vizualization_state)
    {
    case VIZUALIZATION_QUADS:
        VizualizationQuads();
        break;
    case VIZUALIZATION_QUADSTRIP:
        VizualizationQuadStrip();
        break;
    case VIZUALIZATION_TEXTURE:
        VizualizationTexture();
        break;

    }
}

void View::keyPressEvent(QKeyEvent* event)
{
    if (event->nativeVirtualKey() == Qt::Key_U)
    {
        switch (axes)
        {
        case XY:
        {
            layer = min(layer + 1, data.getDepth() - 1);
            break;
        }
        case XZ:
        {
            layer = min(layer + 1, data.getHeight() - 1);
            break;
        }
        case YZ:
        {
            layer = min(layer + 1, data.getWidth() - 1);
            break;
        }
        }
    }
    else
    {
        if (event->nativeVirtualKey() == Qt::Key_D)
        {
            layer = max(layer - 1, 0);
        }
        else
        {
            if (event->nativeVirtualKey() == Qt::Key_N)
            {
                switch (vizualization_state)
                {
                case VIZUALIZATION_QUADS:
                {
                    vizualization_state = VIZUALIZATION_QUADSTRIP;
                    break;
                }
                case VIZUALIZATION_QUADSTRIP:
                {
                    vizualization_state = VIZUALIZATION_TEXTURE;
                    break;
                }
                case VIZUALIZATION_TEXTURE:
                    vizualization_state = VIZUALIZATION_QUADS;
                    break;
                }
            }
        }
    }
    switch (axes)
    {
    case XY:
    {
        layer = min(layer + 1, data.getDepth() - 1);
        break;
    }
    case XZ:
    {
        layer = min(layer + 1, data.getHeight() - 1);
        break;
    }
    case YZ:
    {
        layer = min(layer + 1, data.getWidth() - 1);
        break;
    }
    }
    
    update();
}

void View::Load2dTexture()
{
    glBindTexture(GL_TEXTURE_2D, VBOtexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void View::genTextureImage()
{
    int w = data.getWidth();
    int h = data.getHeight();
    int d = data.getDepth();

    switch (axes)
    {
    case XY:
    {
        textureImage = QImage(w, h, QImage::Format_RGB32);

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int c = (int)(255*TransferFunction(data[layer * w * h + w * y + x]));
                QColor cc(c, c, c);
                textureImage.setPixelColor(x, y, cc);
            }
        }
        break;
    }
    case XZ:
    {
        textureImage = QImage(w, d, QImage::Format_RGB32);

        for (int z = 0; z < d - 1; z++)
        {
            for (int x = 0; x < w - 1; x++)
            {
                int c = (int)(255*TransferFunction(data[z * h * w + layer * w + x]));
                QColor cc(c, c, c);
                textureImage.setPixelColor(x, z, cc);
            }
        }
        break;
    }
    case YZ:
    {
        textureImage = QImage(h, d, QImage::Format_RGB32);

        for (int z = 0; z < d - 1; z++)
        {
            for (int y = 0; y < h - 1; y++)
            {
                int c = (int)(255*TransferFunction(data[z * w * h + y * w + layer]));
                QColor cc(c, c, c);
                textureImage.setPixelColor(y, z, cc);
            }
        }
        break;
    }
    }
    
}

void View::LoadData(std::string fn) {
    data.ReadFile(fn);
}