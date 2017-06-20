#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define KEY_ESC 27
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#define SHIP_ROTATE_SPEED 0.05
#define RAD_TO_DEG(rad) (rad * (180 / M_PI))
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))
#include <fstream>
#include <GL/glext.h>
#include "TextureManager.h"
#include "Boid.h"
//#include "glut.h"
using namespace std;
#define RED 0.6
#define GREEN 0.8
#define BLUE 1
#define ALPHA 1

#define ECHAP 27
int cont=0;
float delta_x = 0.0;
float delta_y = 45.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -450.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)
GLint texturaMar;
class Flock //Cardumen
{
    public:
    vector<Boid> boids;
    vector<Vector3D> obstaculos;
    Flock() {}
    void run()
    {
        for (int i = 0; i < (int)boids.size(); i++)
        {
            if(i<=5)
            {
                glColor3f(0,0,0);
            }
            else
                glColor3f(0,0,1);
            boids[i].run(boids,obstaculos);
        }
        glColor3f(0.4,0.4,0.4);
//
//        for (int i = 0; i < (int)obstaculos.size(); i=i+5)
//        {
//            glPushMatrix();
//                glTranslatef(obstaculos[i].x,0.0f,obstaculos[i].y);
//                glutSolidCube(10);
//            glPopMatrix();
//        }
    }
    void addBoid(Boid b)
    {
        boids.push_back(b);
    }
    void addObst(Vector3D b)
    {
        obstaculos.push_back(b);
    }
};

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);

//function called on each frame
GLvoid window_idle();
Flock flock;
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 1.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 1.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 1.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 1.5;
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
    case GLUT_KEY_F1:
        cout<<"hola"<<endl;
        flock.addBoid( Boid( Vector3D(0,0),0.1,0.05f));
        break;
    case GLUT_KEY_F2:
        flock.addObst(Vector3D(5,5));
        flock.addObst(Vector3D(-5,5));
        flock.addObst(Vector3D(5,-5));
        flock.addObst(Vector3D(-5,-5));
        flock.addObst(Vector3D(0,5));
        flock.addObst(Vector3D(5,0));
        break;

	}
}
GLdouble x=0;
GLdouble y=0;
GLdouble z=0;

void project(int x_cursor, int y_cursor)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX,winY;
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    // obtain the Z position (not world coordinates but in range 0 - 1)
    GLfloat z_cursor;
    winX = (float)x_cursor;
    winY = (float)viewport[3]-(float)y_cursor;
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

    // obtain the world coordinates

    gluUnProject(winX, winY, z_cursor, modelview, projection, viewport, &x, &y, &z);
}
///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
bool butt=0;
GLvoid callback_mouse(int button, int state, int x_cursor, int y_cursor)
{
	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON ||button == GLUT_RIGHT_BUTTON || button == GLUT_MIDDLE_BUTTON))
	{
		mouse_x = x_cursor;
		mouse_y = y_cursor;
	}
	if(button == GLUT_LEFT_BUTTON)
         butt=1;
    if(button == GLUT_MIDDLE_BUTTON)
    {
        butt=0;
        if(state == GLUT_UP)
        {
            int width=400;
            int height=400;
            project(mouse_x,mouse_y);
            flock.addObst(Vector3D(x,z));
            flock.addObst(Vector3D(x+10,z+10));
            flock.addObst(Vector3D(x-10,z+10));
            flock.addObst(Vector3D(x-10,z-10));
            flock.addObst(Vector3D(x+10,z-10));
        }
    }
    if(button == GLUT_RIGHT_BUTTON)
    {
        butt=0;
        if(state == GLUT_UP)
        {
            int width=400;
            int height=400;
            cout<<mouse_x<<" "<<mouse_y<<endl;
            project(mouse_x,mouse_y);
            flock.addBoid(Boid( Vector3D(x,z),0.1,0.05f));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
    if(butt)
    {
    cout<<"x"<<"y"<<endl;
	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
    }
}

int randOP(){
    return rand()%400 - 200;

}
void Iniciar(){
    for (int i = 0; i < 500; i++)
    {
        flock.addBoid( Boid( Vector3D(randOP(),rand()%200+10,randOP()),0.8,0.1f));
    }
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Boids");
	texturaMar = TextureManager::Inst()->LoadTexture("texturaMar.jpg",GL_BGR_EXT,GL_RGB);
	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
    glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&callback_special);
	glutIdleFunc(&window_idle);
	glutMainLoop();
	return 1;
}



void Mar(int tamMar, int X, int Y, int Z)
{
    float tam = tamMar/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaMar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(X-tam,Y ,Z-tam);
    glTexCoord2f(0.0, 1.0);
	glVertex3f(X-tam,Y ,Z+tam);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X+tam,Y ,Z+tam);
    glTexCoord2f(1.0, 0.0);
	glVertex3f(X+tam ,Y ,Z-tam);
	glEnd();

//	glDisable(GL_TEXTURE_2D);
}

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
        srand(time(NULL));
	//enable light : try without it
//	glLightfv(GL_LIGHT0, GL_POSITION, position);
//	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
//	glEnable(GL_LIGHT0);
    Iniciar();

	//shading model : try GL_FLAT
//	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	//enable material : try without it
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

int a=0;
GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.01f, 1000.0f);
//	glOrtho(-150.0f, 150.0f, -150.0f, 150.0f, -150.0f, 150.0f);
    glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);
    glColor3f(1,1,1);
    Mar(500,0,-10,0);
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(x, y,z);
        glEnd();
    flock.run();
    glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 300.0f, 0.0f, 300.0f, 0.0f, 300.0f);
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
