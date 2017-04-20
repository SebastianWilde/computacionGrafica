#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1
#define ECHAP 27
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();
float a = 0;
bool esfera = 1;
GLfloat rotacionX = 0.0f;
GLfloat rotacionY = 0.0f;

GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotacionX -= 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_DOWN:
		rotacionX += 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_LEFT:
	    rotacionY -= 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_RIGHT:
		rotacionY += 3.0f;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;
	}
}


GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
	}
}

GLvoid callback_motion(int x, int y)
{

	glutPostRedisplay();
}

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);
	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(RED, GREEN, BLUE, ALPHA);
}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    /*Pregunta 2*/
    gluPerspective(45.0f,(GLfloat)(800/600),0.01f,100.0f);
    /*Pregunta 3*/
    gluLookAt(cos(3*a),40,sin(3*a),10*cos(3*a),10*sin(3*a),0,0,0,1);
    a += 0.01;
    if (a == 1.0) a = 0.0;
     /*Ejercicios del 1*/
    glRotatef(a,0,0,1);
    glColor3d(255,255,0);
    glutSolidSphere(4,8,8); // el sol

    glPushMatrix();
        glTranslatef(10*cos(3*a),10*sin(3*a),0);
        glColor3d(0,0,255);
        glutSolidSphere(2,8,8); // la tierra

        glColor3d(215,215,215);
        glTranslatef(3*cos(6*a),3*sin(6*a),0);
        glutSolidSphere(1,8,8); //la luna
    glPopMatrix();

    glTranslatef(18*cos(a),18*sin(a),0);
    glColor3d(254,0,0);
    glutSolidSphere(2,8,8); // marte

    /*Pregunta 4*/
//    glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
//    glPushMatrix();
//    glRotatef(rotacionX,1.0,0.0,0.0);
//    glRotatef(rotacionY,0.0,1.0,0.0);
//    glBegin(GL_LINES);
//    glColor3d(255,0,0);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(30.0, 0.0, 0.0);
//    glColor3d(0,255,0);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 30.0, 0.0);
//    glColor3d(0,0,255);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.0, 0.0, 30.0);
//    glEnd();
//    glPopMatrix();


	glutSwapBuffers();


	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

	glMatrixMode(GL_MODELVIEW);
}

void init_scene()
{

}

GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		exit(1);
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}
}


//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : Transformaciones 3D-2");
	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);
    glutSpecialFunc(&callback_special);
    glutMouseFunc(&callback_mouse);
    glutMotionFunc(&callback_motion);
	//function called on each frame
	glutIdleFunc(&window_idle);
	glutMainLoop();

	return 1;
}


