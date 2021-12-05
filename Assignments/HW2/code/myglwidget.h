#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <GL/glew.h>

class MyGLWidget : public QOpenGLWidget{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    
    // 绘制机器人的躯干和四肢
    void drawHead();
    void drawBody();
    void drawArm();
    void drawLeg();

private:
    QTimer *timer;

    GLfloat angle_rotate; // 机器人旋转的角度
    GLfloat w;  // 决定机器人旋转的速度

    GLfloat angle_move; // 机器人手臂和腿摆动的角度
    GLfloat r;  // 决定机器人四肢摆动的速度
};
#endif // MYGLWIDGET_H


//#ifndef MYGLWIDGET_H
//#define MYGLWIDGET_H
//
//#ifdef MAC_OS
//#include <QtOpenGL/QtOpenGL>
//#else
//#include <GL/glew.h>
//#define GLUT_DISABLE_ATEXIT_HACK
//#endif
//#include <QtGui>
//#include <QOpenGLWidget>
//#include <QOpenGLFunctions>
//
//class MyGLWidget : public QOpenGLWidget {
//  Q_OBJECT
//
//public:
//  MyGLWidget(QWidget* parent = nullptr);
//  ~MyGLWidget();
//
//protected:
//  void initializeGL();
//  void paintGL();
//  void resizeGL(int width, int height);
//  void DrawBody();
//  void DrawShoulder();
//  void DrawHip();
//  void DrawArm();
//  void DrawLeg();
//  void DrawHead();
//  void DrawNeck();
//
//private:
//  QTimer* timer;
//  float angleofllarm, angleofluarm, angleofrlarm, angleofruarm, angleofluleg, angleofruleg, angleofllleg, angleofrlleg;
//  float llarm, rlarm, llleg, rlleg, uarm, uleg, angle, c;
//  float angle1, angle2;
//};
//#endif // MYGLWIDGET_H

