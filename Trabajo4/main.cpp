#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
//#include "TextureManager.h"
#include "imageloader.h"
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
GLuint texturaPiso, texturaCasa, texturaTecho, texturaTronco, texturaHojas;

void init_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


//variables para el gizmo
float delta_x = 0.0;
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_y = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)

//Materiales piso
GLfloat pisoAmbiente [3] = {0.0,0.05,0.0};
GLfloat pisoDifuso [3] = {0.4,0.5,0.4};
GLfloat pisoEspecular [3] = {0.04,0.7,0.04};
//Materiales casa
GLfloat casaAmbiente [3] = {0.05,0.0,0.0};
GLfloat casaDifuso [3] = {0.5,0.4,0.4};
GLfloat casaEspecular [3] = {0.7,0.04,0.04};
//Materiales techo
GLfloat techoAmbiente [3] = {0.25,0.20725,0.20725};
GLfloat techoDifuso [3] = {1,0.829,0.829};
GLfloat techoEspecular [3] = {0.296648,0.296648,0.296648};
//Materiales arbol
GLfloat arbolAmbiente [3] = {0.25,0.25,0.25};
GLfloat arbolDifuso [3] = {0.4,0.4,0.4};
GLfloat arbolEspecular [3] = {0.774597,0.774597,0.774597};
///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
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



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{

	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


//function called on each frame
GLvoid window_idle();

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 4 : Escena 3D");
	initGL();
	init_scene();
    Image * image = loadBMP("C:/Users/Sebastian/Pictures/grass.bmp");
	texturaPiso = loadTexture(image);
	image = loadBMP("C:/Users/Sebastian/Pictures/roof.bmp");
	texturaTecho = loadTexture(image);
    image = loadBMP("C:/Users/Sebastian/Pictures/bricks.bmp");//("C:/Users/Sebastian/Pictures/background.bmp");
    texturaCasa = loadTexture(image);
    image = loadBMP("C:/Users/Sebastian/Pictures/tronco.bmp");
    texturaTronco = loadTexture(image);
    image = loadBMP("C:/Users/Sebastian/Pictures/hojas.bmp");
    texturaHojas = loadTexture(image);
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

	GLfloat light0Ambient [] = {0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat light0Dif [] = {1.0f, 1.0f, 0.2f, 1.0f};
	GLfloat light0Spec [] = {0.0f, 2.0f, 2.0f, 1.0f};
	GLfloat light0Pos [] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH); // modelo de shading try GL_FLAT
    //glEnable(GL_CULL_FACE); //no trata las caras escondidas
    glEnable(GL_DEPTH_TEST); // Activa el Z-Buffer
    glDepthFunc(GL_LEQUAL); //Modo de funcionamiento del Z-Buffer
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Activa la corrección de perspectiva
	glClearColor(RED, GREEN, BLUE, ALPHA);
}


void Gizmo3D(){
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


void Suelo()
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.078125*128.0);
    float var_x = 0;
    float var_z = 0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPiso);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        //glColor3f(0.0f,1.0f,0.0f);
        glTexCoord2f(0.0,70.0);
        glVertex3f(var_x - 40,0,var_z+40);
        //glColor3f(0.0f,1.0f,0.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x + 40,0,var_z+40);
        //glColor3f(0.0f,1.0f,0.0f);
        glTexCoord2f(70.0,0.0);
        glVertex3f(var_x+ 40,0,var_z-40);
        //glColor3f(0.0f,1.0f,0.0f);
        glTexCoord2f(70.0,70.0);
        glVertex3f(var_x-40,0,var_z-40);
    glEnd();
    return;
}

void Casa()
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.078125*128.0);
    float var_x =0;
    float var_y = 0;
    float var_z = 0;
    //Muros
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaCasa);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // front
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,2.0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(4.0,2.0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(4.0,0.0);
        glVertex3f(var_x+10,var_y+0,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  // back
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,2.0);
        glVertex3f(var_x-10,var_y+10,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(4.0,2.0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(4.0,0.0);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x-10,var_y+0,var_z-10);
    glEnd();
    glBegin(GL_QUADS);  // right
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,2.0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(2.0,2.0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(2.0,0.0);
        glVertex3f(var_x+10,var_y+0,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x+10,var_y+0,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  // left
        //glColor3f(1.0f,0.0f,0.0f);
         glTexCoord2f(0.0,2.0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(2.0,2.0);
        glVertex3f(var_x-10,var_y+10,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(2.0,0.0);
        glVertex3f(var_x-10,var_y+0,var_z-10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x-10,var_y+0,var_z+10);
    glEnd();
    glPopMatrix();


    //Techo
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,techoAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,techoDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,techoEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.088*128.0);
    glBindTexture(GL_TEXTURE_2D, texturaTecho);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // front
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(0.0,2.0);
        glVertex3f(var_x-10,var_y+15,var_z+0);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(4.0,2.0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(4.0,0.0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
    glEnd();
    glBegin(GL_QUADS);  // back
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(0.0,2.0);
        glVertex3f(var_x-10,var_y+15,var_z+0);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(4.0,2.0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(4.0,0.0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
        //glColor3f(3.0f,3.0f,3.0f);
        glTexCoord2f(0.0,0.0);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,casaEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.078125*128.0);
    glBindTexture(GL_TEXTURE_2D, texturaCasa);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);  // right
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,1.0);
        glVertex3f(var_x+10,var_y+15,var_z+0);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(var_x+10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(-1.0,0.0);
        glVertex3f(var_x+10,var_y+10,var_z-10);
    glEnd();
    glBegin(GL_TRIANGLES);  // left
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(0.0,1.0);
        glVertex3f(var_x-10,var_y+15,var_z+0);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(var_x-10,var_y+10,var_z+10);
        //glColor3f(1.0f,0.0f,0.0f);
        glTexCoord2f(-1.0,0.0);
        glVertex3f(var_x-10,var_y+10,var_z-10);
    glEnd();
    glPopMatrix();
    return;
}

void Arbol()
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,arbolAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,arbolDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,arbolEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.6*128.0);
    GLUquadricObj * obj = gluNewQuadric();
    gluQuadricTexture(obj,GL_TRUE);
    glTranslatef(-20,8,10);
    glPushMatrix();
    glRotatef(90,1,0,0);
    glBindTexture(GL_TEXTURE_2D,texturaTronco);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluCylinder(obj,1,1,8,10,10);
    glPopMatrix();
    //Materiales de la copa del arbol igual a los del suelo
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoAmbiente);
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoDifuso);
    glMaterialfv(GL_FRONT,GL_AMBIENT,pisoEspecular);
    glMaterialf(GL_FRONT,GL_AMBIENT,0.078125*128.0);
    glTranslatef(0,3,0);
    glBindTexture(GL_TEXTURE_2D,texturaHojas);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluSphere(obj,4,10,10);
    return;

}

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);
    gluLookAt(0,30,40,0,15,0,0,1,0);
	glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);
    Suelo();//Piso
    Casa();//Casa
    Arbol();//Arbol
	Gizmo3D();
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
