#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include <fstream>
using namespace std;
#include "Terreno.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


//variables para el gizmo
float delta_x = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = -2500.0;
float var_z = -5000.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)
Terreno malla;

GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 100;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 100;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 100;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 100;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

GLvoid callback_motion(int x, int y)
{

	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}


//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP  : Modelo digital del terreno");
    malla.load("fontvieille.txt");
	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);
	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}



GLvoid initGL()
{

	glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glClearColor(RED, GREEN, BLUE, ALPHA);
}


void Gizmo3D()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();
	return;
}



GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.01f, 100000.0f);
    glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);
    malla.display();
	glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

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







///*
// * GLUT Shapes Demo
// *
// * Written by Nigel Stewart November 2003
// *
// * This program is test harness for the sphere, cone
// * and torus shapes in GLUT.
// *
// * Spinning wireframe and smooth shaded shapes are
// * displayed until the ESC or q key is pressed.  The
// * number of geometry stacks and slices can be adjusted
// * using the + and - keys.
// */
//
// /*glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); GLFILL*/
//#define GLUT_DISABLE_ATEXIT_HACK
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <windows.h>
//#include <GL/glut.h>
//#endif
//
//#include <math.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <bits/stdc++.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//
//
//
//
///* GLUT callback Handlers */
//
//static void resize(int width, int height)
//{
//    const float ar = (float) width / (float) height;
//
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity() ;
//}
//
//static void display(void)
//{
//    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
//    const double a = t*90.0;
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3d(1,0,0);
//
//    glPushMatrix();
//        glTranslated(-2.4,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidSphere(1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(0,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidCone(1,1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(2.4,1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutSolidTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(-2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireSphere(1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(0,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireCone(1,1,slices,stacks);
//    glPopMatrix();
//
//    glPushMatrix();
//        glTranslated(2.4,-1.2,-6);
//        glRotated(60,1,0,0);
//        glRotated(a,0,0,1);
//        glutWireTorus(0.2,0.8,slices,stacks);
//    glPopMatrix();
//
//    glutSwapBuffers();
//}
//
//
//static void key(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//        case 27 :
//        case 'q':
//            exit(0);
//            break;
//
//        case '+':
//            slices++;
//            stacks++;
//            break;
//
//        case '-':
//            if (slices>3 && stacks>3)
//            {
//                slices--;
//                stacks--;
//            }
//            break;
//    }
//
//    glutPostRedisplay();
//}
//
//static void idle(void)
//{
//    glutPostRedisplay();
//}
//
//const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
//
//const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
//const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
//const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
//const GLfloat high_shininess[] = { 100.0f };
//
///* Program entry point */
//
//int main(int argc, char *argv[])
//{
//    glutInit(&argc, argv);
//    glutInitWindowSize(640,480);
//    glutInitWindowPosition(10,10);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//
//    glutCreateWindow("GLUT Shapes");
//
//    glutReshapeFunc(resize);
//    glutDisplayFunc(display);
//    glutKeyboardFunc(key);
//    glutIdleFunc(idle);
//
//    glClearColor(1,1,1,1);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//
//    glEnable(GL_LIGHT0);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
//
//    glutMainLoop();
//
//    return EXIT_SUCCESS;
//}
