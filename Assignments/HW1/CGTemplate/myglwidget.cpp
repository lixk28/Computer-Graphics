#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent),
	scene_id(0)
{
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);
}

void MyGLWidget::paintGL()
{
	if (scene_id == 0) {
		scene_0();
	}
	else if (scene_id == 1) {
		scene_1();
	}
	else if (scene_id == 2) {
		scene_2();
	}
	else if (scene_id == 3) {
		scene_3();
	}
}

void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
	//Press 0, 1, 2, 3 to switch the scene
	if (e->key() == Qt::Key_0) {
		scene_id = 0;
		update();
	}
	else if (e->key() == Qt::Key_1) {
		scene_id = 1;
		update();
	}
	else if (e->key() == Qt::Key_2) {
		scene_id = 2;
		update();
	}
	else if (e->key() == Qt::Key_3) {
		scene_id = 3;
		update();
	}
}

void MyGLWidget::scene_0()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(50.0f, 50.0f, 0.0f);
	
	//draw a diagonal "I"
	glPushMatrix();
	glColor3f(0.839f, 0.153f, 0.157f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.5f, -22.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(5.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);

	glVertex2f(5.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);
	glVertex2f(5.0f, 45.0f);

	glEnd();
	glPopMatrix();	
}

// Use GL_TRIANGLES to paint
void MyGLWidget::scene_1()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width() / 2, width() / 2, -height() / 2, height() / 2, -1000.0f, 1000.0f);
	//gluPerspective(60.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);
	gluLookAt(0.0, 0.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 40.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //your implementation here, maybe you should write several glBegin
	glPushMatrix();
	//your implementation
	glColor3f(0.1f, 0.6f, 1.0f);	// blue

	// draw L
	glBegin(GL_TRIANGLES);
	glVertex2f(-100.0f, 60.0f);
	glVertex2f(-100.0f, 0.0f);
	glVertex2f(-90.0f, 10.0f);

	glVertex2f(-100.0f, 60.0f);
	glVertex2f(-90.0f, 10.0f);
	glVertex2f(-90.0f, 60.0f);

	glVertex2f(-100.0f, 0.0f);
	glVertex2f(-90.0f, 10.0f);
	glVertex2f(-60.0f, 0.0f);

	glVertex2f(-90.0f, 10.0f);
	glVertex2f(-60.0f, 0.0f);
	glVertex2f(-60.0f, 10.0f);
	glEnd();

	// draw X
	glBegin(GL_TRIANGLES);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-10.0f, 0.0f);
	glVertex2f(-5.0f, 30.0f);

	glVertex2f(-10.0f, 0.0f);
	glVertex2f(-5.0f, 30.0f);
	glVertex2f(5.0f, 30.0f);

	glVertex2f(-5.0f, 30.0f);
	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 60.0f);

	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 60.0f);
	glVertex2f(20.0f, 60.0f);

	glVertex2f(-20.0f, 60.0f);
	glVertex2f(-10.0f, 60.0f);
	glVertex2f(-5.0f, 30.0f);

	glVertex2f(-10.0f, 60.0f);
	glVertex2f(-5.0f, 30.0f);
	glVertex2f(0.0f, 40.0f);

	glVertex2f(0.0f, 20.0f);
	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 0.0f);

	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);

	glEnd();

	// draw K
	glBegin(GL_TRIANGLES);
	glVertex2f(60.0f, 0.0f);
	glVertex2f(70.0f, 0.0f);
	glVertex2f(60.0f, 60.0f);

	glVertex2f(70.0f, 0.0f);
	glVertex2f(60.0f, 60.0f);
	glVertex2f(70.0f, 60.0f);

	glVertex2f(70.0f, 30.0f);
	glVertex2f(80.0f, 30.0f);
	glVertex2f(90.0f, 60.0f);

	glVertex2f(80.0f, 30.0f);
	glVertex2f(90.0f, 60.0f);
	glVertex2f(100.0f, 60.0f);

	glVertex2f(70.0f, 30.0f);
	glVertex2f(80.0f, 30.0f);
	glVertex2f(90.0f, 0.0f);

	glVertex2f(90.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	glVertex2f(80.0f, 30.0f);
	glEnd();

	glPopMatrix();
}

// Use GL_TRIANGLE_STRIP to paint
void MyGLWidget::scene_2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width(), 0.0f, height(), -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);

	glPushMatrix();
	glColor3f(0.3f, 0.9f, 0.3f);	// green
	
	// draw L
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-100.0f, 60.0f);
	glVertex2f(-90.0f, 60.0f);
	glVertex2f(-100.0f, 0.0f);
	glVertex2f(-90.0f, 10.0f);
	glVertex2f(-60.0f, 0.0f);
	glVertex2f(-60.0f, 10.0f);
	glEnd();

	// draw X
	// draw the top part of X
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-20.0f, 60.0f);
	glVertex2f(-10.0f, 60.0f);
	glVertex2f(-5.0f, 30.0f);
	glVertex2f(0.0f, 40.0f);
	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 60.0f);
	glVertex2f(20.0f, 60.0f);
	glEnd();

	// draw the bottom part of X
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-10.0f, 0.0f);
	glVertex2f(-5.0f, 30.0f);
	glVertex2f(0.0f, 20.0f);
	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glEnd();

	// draw K
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(60.0f, 60.0f);
	glVertex2f(60.0f, 0.0f);
	glVertex2f(70.0f, 60.0f);
	glVertex2f(70.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(90.0f, 60.0f);
	glVertex2f(100.0f, 60.0f);
	glVertex2f(70.0f, 30.0f);
	glVertex2f(80.0f, 30.0f);
	glVertex2f(90.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

// Use GL_QUAD_STRIP to paint
void MyGLWidget::scene_3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width(), 0.0f, height(), -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);

	glPushMatrix();
	glColor3f(0.4f, 0.3f, 0.9f);	// purple

	// draw L
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-100.0f, 60.0f);
	glVertex2f(-90.0f, 60.0f);
	glVertex2f(-100.0f, 0.0f);
	glVertex2f(-90.0f, 10.0f);
	glVertex2f(-60.0f, 0.0f);
	glVertex2f(-60.0f, 10.0f);
	glEnd();

	// draw X
	glBegin(GL_QUAD_STRIP);
	glVertex2f(-20.0f, 60.0f);
	glVertex2f(-10.0f, 60.0f);
	glVertex2f(10.0f, 0.0f);
	glVertex2f(20.0f, 0.0f);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2f(-20.0f, 0.0f);
	glVertex2f(-10.0f, 0.0f);
	glVertex2f(-5.0f, 30.0f);
	glVertex2f(0.0f, 20.0f);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2f(0.0f, 40.0f);
	glVertex2f(5.0f, 30.0f);
	glVertex2f(10.0f, 60.0f);
	glVertex2f(20.0f, 60.0f);
	glEnd();

	// draw K
	glBegin(GL_QUAD_STRIP);
	glVertex2f(60.0f, 60.0f);
	glVertex2f(70.0f, 60.0f);
	glVertex2f(60.0f, 0.0f);
	glVertex2f(70.0f, 0.0f);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex2f(90.0f, 60.0f);
	glVertex2f(100.0f, 60.0f);
	glVertex2f(70.0f, 30.0f);
	glVertex2f(80.0f, 30.0f);
	glVertex2f(90.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	glEnd();

	glPopMatrix();
}