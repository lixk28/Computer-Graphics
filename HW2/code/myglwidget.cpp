#include "myglwidget.h"

/*###################################################
##  函数: MyGLWidget
##  函数描述： MyGLWidget类的构造函数，实例化定时器timer
##  参数描述：
##  parent: MyGLWidget的父对象
#####################################################*/
MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent)
{
	timer = new QTimer(this); // 实例化一个定时器
	timer->start(16); // 时间间隔设置为16ms，可以根据需要调整
	connect(timer, SIGNAL(timeout()), this, SLOT(update())); // 连接update()函数，每16ms触发一次update()函数进行重新绘图
	
	angle_rotate = 0.5f;  // 机器人旋转的角度
  w = 0.05f; // 旋转的速度

  angle_move = 0.0f;  // 机器人四肢摆动的角度
  r = 0.5f; // 摆动的速度
}


/*###################################################
##  函数: ~MyGLWidget
##  函数描述： ~MyGLWidget类的析构函数，删除timer
##  参数描述： 无
#####################################################*/
MyGLWidget::~MyGLWidget()
{
	delete this->timer;
}


/*###################################################
##  函数: initializeGL
##  函数描述： 初始化绘图参数，如视窗大小、背景色等
##  参数描述： 无
#####################################################*/
void MyGLWidget::initializeGL()
{
	glViewport(0, 0, width(), height());  
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);  // 开启深度测试
}


/*###################################################
##  函数: paintGL
##  函数描述： 绘图函数，实现图形绘制，会被update()函数调用
##  参数描述： 无
#####################################################*/
void MyGLWidget::paintGL()
{
	// Your Implementation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, width() / height(), 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -35.0f); // 设置机器人旋转的中心为 (0, 0, -35)
	glRotatef(-angle_rotate, 0.0f, 1.0f, 0.0f);	// 每次绕 Y 轴旋转 -angle_rotate 度

  // 绘制机器人
  glPushMatrix(); // 保存当前位置，即旋转中心的位置
  {
    glTranslatef(0.0f, 0.0f, 10.0f);	// 设置运动半径为 10
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);	// 设置为切线朝向
    glPushMatrix(); // 保存当前位置，即机器人中心的位置
    {
      drawBody(); // 绘制机器人身体

      glPushMatrix();
      {
        glTranslatef(0.0f, 2.4f, 0.0f); // 移动到机器人头部顶部中心
        drawHead(); // 绘制机器人头部
      }
      glPopMatrix();

      glPushMatrix();
      {
        glTranslatef(-1.25f, 1.0f, 0.0f); // 移动到机器人左臂顶部中心
        glRotatef(angle_move, 1.0f, 0.0f, 0.0f); // 左臂转动
        drawArm();  // 绘制机器人左臂
      }
      glPopMatrix();

      glPushMatrix();
      {
        glTranslatef(1.25f, 1.0f, 0.0f); // 移动到机器人右臂顶部中心
        glRotatef(-angle_move, 1.0f, 0.0f, 0.0f);  // 右臂转动
        drawArm();  // 绘制机器人右臂
      }
      glPopMatrix();

      glPushMatrix();
      {
        glTranslatef(-0.5f, -2.0f, 0.0f);  // 移动到机器人左腿顶部中心
        glRotatef(-angle_move, 1.0f, 0.0f, 0.0f);  // 左腿转动
        drawLeg();  // 绘制机器人左腿
      }
      glPopMatrix();

      glPushMatrix();
      {
        glTranslatef(0.5f, -2.0f, 0.0f);  // 移动到机器人右腿顶部中心
        glRotatef(angle_move, 1.0f, 0.0f, 0.0f); // 右腿转动
        drawLeg();  // 绘制机器人右腿
      }
      glPopMatrix();
    }
    glPopMatrix();
  }
  glPopMatrix();

  angle_rotate += w; // 旋转变换的角度增加 w

  // 手臂和腿的旋转角度
  // 左臂和右腿一起转相同的角度
  // 右臂和左腿一起转相同的角度
  if (angle_move >= 45.0f || angle_move <= -45.0f)
  {
    angle_move = 0.95 * angle_move; // a stupid bug here
    r = -r;
  }
  else
  {
    angle_move += r;  // 摆动的角度增加 r
  }
}

/*###################################################
##  函数: drawHead
##  函数描述： 绘制机器人的脑袋
##  参数描述： 无
#####################################################*/
void MyGLWidget::drawHead()
{
  glColor3f(0.72f, 0.57f, 0.55f);
  glBegin(GL_QUADS);
  //正面
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  //背面
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  //左面
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  //右面
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  //顶面
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  //底面
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glEnd();
}

/*###################################################
##  函数: drawBody
##  函数描述： 绘制机器人的身体
##  参数描述： 无
#####################################################*/
void MyGLWidget::drawBody()
{
  glColor4f(0.10f, 0.79f, 0.87f, 1.0f);
  glBegin(GL_QUADS);
  //正面
  glVertex3f(-1.0f, 2.0f, 0.5f);
  glVertex3f(1.0f, 2.0f, 0.5f);
  glVertex3f(1.0f, -2.0f, 0.5f);
  glVertex3f(-1.0f, -2.0f, 0.5f);
  //背面
  glVertex3f(1.0f, 2.0f, -0.5f);
  glVertex3f(-1.0f, 2.0f, -0.5f);
  glVertex3f(-1.0f, -2.0f, -0.5f);
  glVertex3f(1.0f, -2.0f, -0.5f);
  //左面
  glVertex3f(-1.0f, 2.0f, 0.5f);
  glVertex3f(-1.0f, 2.0f, -0.5f);
  glVertex3f(-1.0f, -2.0f, -0.5f);
  glVertex3f(-1.0f, -2.0f, 0.5f);
  //右面
  glVertex3f(1.0f, 2.0f, 0.5f);
  glVertex3f(1.0f, 2.0f, -0.5f);
  glVertex3f(1.0f, -2.0f, -0.5f);
  glVertex3f(1.0f, -2.0f, 0.5f);
  //顶面
  glVertex3f(1.0f, 2.0f, 0.5f);
  glVertex3f(1.0f, 2.0f, -0.5f);
  glVertex3f(-1.0f, 2.0f, -0.5f);
  glVertex3f(-1.0f, 2.0f, 0.5f);
  //底面
  glVertex3f(1.0f, -2.0f, 0.5f);
  glVertex3f(1.0f, -2.0f, -0.5f);
  glVertex3f(-1.0f, -2.0f, -0.5f);
  glVertex3f(-1.0f, -2.0f, 0.5f);
  glEnd();
}

/*###################################################
##  函数: drawArm
##  函数描述： 绘制机器人的手臂
##  参数描述： 无
#####################################################*/
void MyGLWidget::drawArm()
{
  glColor4f(0.71f, 0.55f, 0.50f, 1.0f);
  glBegin(GL_QUADS);
  //正面
  glVertex3f(-0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25f, -2.5f, 0.25f);
  //背面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  glVertex3f(-0.25f, -2.5f, -0.25f);
  //左面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(-0.25f, 0.0f, 0.25f);
  glVertex3f(-0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25f, -2.5f, -0.25f);
  //右面
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  //顶面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(-0.25, 0.0f, 0.25f);
  //底面
  glVertex3f(-0.25f, -2.5f, -0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25, -2.5f, 0.25f);
  glEnd();
}

/*###################################################
##  函数: drawLeg
##  函数描述： 绘制机器人的腿
##  参数描述： 无
#####################################################*/
void MyGLWidget::drawLeg()
{
  glColor4f(0.29f, 0.27f, 0.78f, 1.0f);
  glBegin(GL_QUADS);
  //正面
  glVertex3f(-0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25f, -2.5f, 0.25f);
  //背面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  glVertex3f(-0.25f, -2.5f, -0.25f);
  //左面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(-0.25f, 0.0f, 0.25f);
  glVertex3f(-0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25f, -2.5f, -0.25f);
  //右面
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  //顶面
  glVertex3f(-0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, -0.25f);
  glVertex3f(0.25f, 0.0f, 0.25f);
  glVertex3f(-0.25, 0.0f, 0.25f);
  //底面
  glVertex3f(-0.25f, -2.5f, -0.25f);
  glVertex3f(0.25f, -2.5f, -0.25f);
  glVertex3f(0.25f, -2.5f, 0.25f);
  glVertex3f(-0.25, -2.5f, 0.25f);
  glEnd();
}


/*###################################################
##  函数: resizeGL
##  函数描述： 当窗口大小改变时调整视窗尺寸
##  参数描述： 无
#####################################################*/
void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

