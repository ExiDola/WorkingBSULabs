#include "letter.h"
#include "ui_mainwindow.h"
#include <QDebug>
GLfloat VertexArray[64][3];
//GLubyte IndexArray[13][4];
GLubyte IndexArray[16][4] = {
    {0,1,9,8},
    {0,3,11,8},
    {2,3,11,10},
    {1,2,10,9},
    {0,1,2,3},
    {8,9,10,11},

    {12,13,6,4},
    {13,14,7,6},
    {15,14,7,5},
    {12,15,5,4},
    {12,13,14,15},

    {6,4,17,16},
    {4,5,18,17},
    {5,7,19,18},
    {6,7,19,16},
    {16,17,18,19}
};

letter::letter(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setGeometry(400,200,800,600);

    xRot=0; yRot=0; zRot=0; zTra=-1; nSca=1;
}

void letter::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
    glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов
    glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
}

void letter::resizeGL(int nWidth, int nHeight)
{
}

void letter::paintGL()
{
    glClearColor(1,1,1,0); // цвет фона
    glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом очистки
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины
    glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
    glLoadIdentity();           // загружает единичную матрицу моделирования
    // последовательные преобразования
    glScalef(nSca, nSca, nSca);        // масштабирование
    glTranslatef(0.0f, zTra, 0.0f);  // трансляция
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z
    drawAxis();
    float e=0,r=0,t=0;
    colour.getRgbF(&e,&r,&t,nullptr);
    glColor4f(e, r, t, 0.0f);
    getVertexArray(0.8);
    getIndexArray();
    if(check==1)
    draw_xy_projection();
    else if(check==2)
    draw_xz_projection();
    else if(check==3)
    draw_zy_projection();
    else if(check==4)
    draw_scaling();
    else if(check==5)
    draw_transfer();
    else if(check==6)
    draw_rotation_x();
    else if(check==7)
    draw_rotation_y();
    else if(check==8)
    draw_rotation_z();
    else if(check==9)
    drawFigure();


}

/*virtual*/void letter::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{

   ptrMousePosition = pe->pos();

}

/*virtual*/void letter::mouseReleaseEvent(QMouseEvent* pe)
{

}

/*virtual*/void letter::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 1/M_PI*(GLfloat)(pe->y()-ptrMousePosition.y());
   yRot += 1/M_PI*(GLfloat)(pe->x()-ptrMousePosition.x());
   ptrMousePosition = pe->pos();
   update();
}

/*virtual*/void letter::wheelEvent(QWheelEvent* pe)
{
   if ((pe->angleDelta().y())>0) scale_plus(); else if ((pe->angleDelta().y())<0) scale_minus();
   update(); // обновление изображения
}

/*virtual*/void letter::keyPressEvent(QKeyEvent* pe) // нажатие определенной клавиши
{
   switch (pe->key())
   {
      case Qt::Key_Plus:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Equal:
         scale_plus();     // приблизить сцену
      break;

      case Qt::Key_Minus:
         scale_minus();    // удалиться от сцены
      break;

      case Qt::Key_W:
         rotate_up();      // повернуть сцену вверх
      break;

      case Qt::Key_S:
         rotate_down();    // повернуть сцену вниз
      break;

      case Qt::Key_A:
        rotate_left();     // повернуть сцену влево
      break;

      case Qt::Key_D:
         rotate_right();   // повернуть сцену вправо
      break;

      case Qt::Key_Z:
         translate_down(); // транслировать сцену вниз
      break;

      case Qt::Key_X:
         translate_up();   // транслировать сцену вверх
      break;

      case Qt::Key_Space:  // клавиша пробела
         defaultScene();   // возвращение значений по умолчанию
      break;

      case Qt::Key_Escape: // клавиша "эскейп"
         this->close();    // завершает приложение
      break;
   }

   update(); // обновление изображения
}


void letter::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void letter::scale_minus() // удалиться от сцены
{
   nSca = nSca/1.1;
}

void letter::rotate_up() // повернуть сцену вверх
{
   xRot += 1.0;
}

void letter::rotate_down() // повернуть сцену вниз
{
   xRot -= 1.0;
}

void letter::rotate_left() // повернуть сцену влево
{
   zRot += 1.0;
}

void letter::rotate_right() // повернуть сцену вправо
{
   zRot -= 1.0;
}

void letter::translate_down() // транслировать сцену вниз
{
   zTra -= 0.05;
}

void letter::translate_up() // транслировать сцену вверх
{
   zTra += 0.05;
}

void letter::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}
void letter::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);

   glBegin(GL_LINES);
   glVertex3f( 10.0f,  0.0f,  0.0f);
   glVertex3f(-10.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);

   float e=0,r=0,t=0;
   halfGreen.getRgbF(&e,&r,&t,nullptr);
   glColor4f(e, r, t, 0.0f);

   glBegin(GL_LINES);

   glVertex3f( 0.0f,  10.0f,  0.0f);
   glVertex3f( 0.0f, -10.0f,  0.0f);

   glColor4f(0.00f, 0.00f, 1.00f, 1.0f);

   glVertex3f( 0.0f,  0.0f,  10.0f);
   glVertex3f( 0.0f,  0.0f, -10.0f);

   glColor4f(0.00f, 0.00f, 0.00f, 0.0f);
   for (float i = -10; i < 10; i+=0.25){
      float k = 20.0;
      glBegin(GL_LINES);
      glVertex3f(i, -1.0 / k, 0.0f);
      glVertex3f(i, 1.0 / k, 0.0f);
      glVertex3f(-1.0 / k, i, 0.0f);
      glVertex3f(1.0 / k, i, 0.0f);
      glVertex3f( 0.0f, 1.0 / k, i);
      glVertex3f( 0.0f, -1.0 / k, i);
   }

   glEnd();
}

void letter::getVertexArray(float k){

    VertexArray[0][0]=0;
    VertexArray[0][1]=0;
    VertexArray[0][2]=0;

    VertexArray[1][0]=0.25*k;
    VertexArray[1][1]=0;
    VertexArray[1][2]=0;

    VertexArray[2][0]=0.25*k;
    VertexArray[2][1]=0;
    VertexArray[2][2]=0.25*k;

    VertexArray[3][0]=0;
    VertexArray[3][1]=0;
    VertexArray[3][2]=0.25*k;

    VertexArray[4][0]=0.25*k;
    VertexArray[4][1]=0.75*k;
    VertexArray[4][2]=0;

    VertexArray[5][0]=0.25*k;
    VertexArray[5][1]=0.75*k;
    VertexArray[5][2]=0.25*k;

    VertexArray[6][0]=0.25*k;
    VertexArray[6][1]=k;
    VertexArray[6][2]=0;

    VertexArray[7][0]=0.25*k;
    VertexArray[7][1]=k;
    VertexArray[7][2]=0.25*k;

    VertexArray[8][0]=0;
    VertexArray[8][1]=1.75*k;
    VertexArray[8][2]=0;

    VertexArray[9][0]=0.25*k;
    VertexArray[9][1]=1.75*k;
    VertexArray[9][2]=0;

    VertexArray[10][0]=0.25*k;
    VertexArray[10][1]=1.75*k;
    VertexArray[10][2]=0.25*k;

    VertexArray[11][0]=0;
    VertexArray[11][1]=1.75*k;
    VertexArray[11][2]=0.25*k;

    VertexArray[12][0]=0.75*k;
    VertexArray[12][1]=0;
    VertexArray[12][2]=0;

    VertexArray[13][0]=1*k;
    VertexArray[13][1]=0;
    VertexArray[13][2]=0;

    VertexArray[14][0]=1*k;
    VertexArray[14][1]=0;
    VertexArray[14][2]=0.25*k;

    VertexArray[15][0]=0.75*k;
    VertexArray[15][1]=0;
    VertexArray[15][2]=0.25*k;

    VertexArray[16][0]=0.75*k;
    VertexArray[16][1]=1.75*k;
    VertexArray[16][2]=0;

    VertexArray[17][0]=1*k;
    VertexArray[17][1]=1.75*k;
    VertexArray[17][2]=0;

    VertexArray[18][0]=1*k;
    VertexArray[18][1]=1.75*k;
    VertexArray[18][2]=0.25*k;

    VertexArray[19][0]=0.75*k;
    VertexArray[19][1]=1.75*k;
    VertexArray[19][2]=0.25*k;
}

void letter::getIndexArray()
{

}

void letter::draw_rotation_z()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=cos(angle*(M_PI/180.0));;
    conv[0][1]=-sin(angle*(M_PI/180.0));;
    conv[0][2]=0;

    conv[1][0]=sin(angle*(M_PI/180.0));
    conv[1][1]=cos(angle*(M_PI/180.0));
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    qDebug()<<"Z rotation matrix"<<Qt::endl;
    for(int i=0; i < 3; i++)
    {
    qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
      qDebug()<<Qt::endl;
    }

    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);

}
void letter::draw_rotation_y()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=cos(angle*(M_PI/180.0));
    conv[0][1]=0;
    conv[0][2]=sin(angle*(M_PI/180.0));

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=-sin(angle*(M_PI/180.0));
    conv[2][1]=0;
    conv[2][2]=cos(angle*(M_PI/180.0));

    qDebug()<<"Y rotation matrix"<<Qt::endl;
    for(int i=0; i < 3; i++)
    {
     qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
     qDebug()<<Qt::endl;
    }

    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);

}
void letter::draw_rotation_x()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=cos(angle*(M_PI/180.0));
    conv[1][2]=-sin(angle*(M_PI/180.0));

    conv[2][0]=0;
    conv[2][1]=sin(angle*(M_PI/180.0));
    conv[2][2]=cos(angle*(M_PI/180.0));

    qDebug()<<"X rotation matrix"<<Qt::endl;
    for(int i=0; i < 3; i++)
    {
    qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
     qDebug()<<Qt::endl;
    }

    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     {
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);

}
void letter::draw_transfer()
{
    GLfloat c[64][3];
    GLfloat conv[4][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    conv[3][0]=x_transfer;
    conv[3][1]=y_transfer;
    conv[3][2]=z_transfer;

    qDebug()<<"transfer matrix"<<Qt::endl;
    for(int i=0; i < 4; i++)
    {
       qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
     qDebug()<<Qt::endl;
    }

    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 4; k++)
     {
         if(k==3)
      c[i][j]+=1*conv[k][j];
         else
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
}
void letter::draw_scaling()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=x_scale;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=y_scale;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=z_scale;

    qDebug()<<"scale matrix"<<Qt::endl;
    for(int i=0; i < 3; i++)
    {
     qDebug()<<conv[i][0]<<" "<<conv[i][1]<<" "<<conv[i][2]<<" ";
     qDebug()<<Qt::endl;
    }

    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
}
void letter::draw_xy_projection()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=0;
    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
}
void letter::draw_xz_projection()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=0;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
}
void letter::draw_zy_projection()
{
    GLfloat c[64][3];
    GLfloat conv[3][3] ;
    conv[0][0]=0;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;
    for(int i=0; i < 64; i++)
    {
     for(int j=0; j < 3; j++)
     {
     c[i][j]=0;
     for(int k=0; k < 3; k++)
     c[i][j]+=VertexArray[i][k]*conv[k][j];
     }
    }
    glVertexPointer(3, GL_FLOAT, 0, c);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
}
void letter::drawFigure(){
    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
//  glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_QUADS, 64, GL_UNSIGNED_BYTE, IndexArray);
//  glDisableClientState(GL_VERTEX_ARRAY);
}
