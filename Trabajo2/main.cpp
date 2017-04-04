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
float c = 0;
float b = -8;
bool esfera = 1;
int time = 0;
int timebase = 0;
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 2 : Transformaciones");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	glutReshapeFunc(&window_reshape);

	glutKeyboardFunc(&window_key);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
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
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);

    time = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
    float dt = float(time -timebase)/1000.0;// delta time
    timebase = time;
    /*Ejercicios del 1 al 4 */

//    glTranslated(b,0,0);
//    glutSolidSphere(1,50,50);
//    if (b<=-8) esfera = 1;
//    if (b>=8) esfera = 0;
//    if (esfera == 1) b+=0.01f;
//    else b-=0.01f;
//	/*dibujar aqui*/
//    glRotatef(a,1,0,0);
//    glTranslatef(0,5,0);
//    glutSolidCube(1.4);
//
//
//	glPushMatrix();
//    glRotatef(a,0,0,1);
//    glTranslatef(10,0,0);
//    a+=90*dt;
//    glutSolidTeapot(2.0);
//
//    glRotatef(a*3,0,1,0);
//    glTranslatef(3,0,0);
//    glutSolidTorus(0.2,0.3,5,10);
//    glPopMatrix();

    glRotatef(a,0,0,1);
    glColor3d(255,255,0);
    glutSolidSphere(4,8,8); // el sol



    glPushMatrix();
    glRotatef(3*a,0,0,1);
    glTranslatef(10,0,0);
    glColor3d(0,0,255);
    glutSolidSphere(2,8,8); // la tierra

    glRotatef(a*1.5,0,1,0);
    glTranslatef(3.5,0,0);
    glColor3d(215,215,215);
    glutSolidSphere(1,8,8); //la luna
    glPopMatrix();

    glRotatef(a,0,0,1);
    glTranslatef(18,0,0);
    glColor3d(254,0,0);
    glutSolidSphere(2,8,8); // marte
    c+=90*dt;
    a+=0.03;
    //a+=90*dt;

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
