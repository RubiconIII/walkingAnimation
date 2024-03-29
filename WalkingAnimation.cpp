#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>


static int polyhedron = 0;
int refreshMills = 10;
int tick = 1;

void moveRotate(float rotationAngle, float moveTime);

void init(void)
{	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void timer(int value) {
	glutPostRedisplay();    // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void leg(void)
{	float rotationAngle, moveTime;
	//top leg
	glPushMatrix();
	rotationAngle = 15; moveTime = 2;
	glScalef(0.3, 1.5, 1.0);
	glTranslatef(0.0, 1.0, 0.0);
	moveRotate(rotationAngle, moveTime);
	glutSolidCube(1.0);
	glPopMatrix();

	//bottom leg
	glPushMatrix();
	rotationAngle = -15; moveTime = 2;
	glScalef(0.3, 1.5, 1.0);
	glTranslatef(0, 0.0, 0.0);
	moveRotate(rotationAngle, moveTime);
	glutSolidCube(1.0);
	glPopMatrix();

	//foot (moves with bottom leg)
	glPushMatrix();
	glScalef(1.0, .3, 1.0);
	glTranslatef(.6, -2.0, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

}
void moveRotate(float rotationAngle, float moveTime) {
	glRotatef(rotationAngle * cos(M_PI * tick / 180 / moveTime), 0, 0, 1);

}
void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	leg();
	glFlush();
	tick++;
}

	void reshape(int w, int h)
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -5.0);
	}


	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Walking");

		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		GLfloat light_position[] = { 1, 0, 	0 };

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		init();
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutTimerFunc(0, timer, 0);
		glutMainLoop();
		return 0;
	}