#define GLUT_DISABLE_ATEXIT_HACK

#include <bits/stdc++.h>
#include "TextureManager.h"

#include <GL/gl.h>
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

GLint texture1; /// PISO
GLint texture2; /// NMI 1
GLint texture3; /// NMI 2
GLint texture4; /// NMI 3
GLint texture5; /// CHRCTR

inline int rdtsc()
{
     __asm__ __volatile__("rdtsc");
    return 1;
}

bool Collision(vector<float> x, vector<float> y)
{
    if(y[4]>x[5])
    {
        if((x[1]>y[0] && x[1]<y[1]) || (x[0]<y[1] && x[0]>y[0]) )
        {
            if((x[2]<y[2] && x[3]>y[2]) || ((x[2]<y[3] && x[3]>y[3])))
                return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Juego Parcial");


	initGL();
	init_scene();

	texture1 = TextureManager::Inst()->LoadTexture("/home/mellamoarroz/Downloads/Old_Donwloads/Ejercicios_CPP/JUEGO_PARCIAL/grass.jpg", GL_BGR_EXT, GL_RGB);
	texture2 = TextureManager::Inst()->LoadTexture("/home/mellamoarroz/Downloads/Old_Donwloads/Ejercicios_CPP/JUEGO_PARCIAL/box.jpg", GL_BGR_EXT, GL_RGB);
	texture3 = TextureManager::Inst()->LoadTexture("/home/mellamoarroz/Downloads/Old_Donwloads/Ejercicios_CPP/JUEGO_PARCIAL/lava.jpg", GL_BGR_EXT, GL_RGB);
	texture4 = TextureManager::Inst()->LoadTexture("/home/mellamoarroz/Downloads/Old_Donwloads/Ejercicios_CPP/JUEGO_PARCIAL/wood.jpg", GL_BGR_EXT, GL_RGB);
	texture5 = TextureManager::Inst()->LoadTexture("/home/mellamoarroz/Downloads/Old_Donwloads/Ejercicios_CPP/JUEGO_PARCIAL/metal.jpg", GL_BGR_EXT, GL_RGB);
	srand(rdtsc());

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
	GLfloat position[] = { 0.0f, 5.0f, 0.0f, 0.0 };

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

///Box
vector<float> Box={-5,5,1,20,0,-10};

///Enemigo1
vector<float> E1={-5.0,5.0,1.0,10.0,-160.0,-170.0};

///Enemigo2
vector<float> E2={-5.0,5.0,1.0,10.0,-160.0,-170.0};

///Enemigo3
vector<float> E3={-30.0,30.0,10.0,20.0,-160.0,-170,0};

GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	    Box[2]=1.0;
	    Box[3]=20.0;

	    Box[4]-=1;
	    Box[5]-=1;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_DOWN:
	    Box[2]=1.0;
	    Box[3]=20.0;

	    Box[4]+=1;
	    Box[5]+=1;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_LEFT:
	    Box[2]=1.0;
	    Box[3]=20.0;

	    Box[0]-=1;
	    Box[1]-=1;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case GLUT_KEY_RIGHT:
	    Box[2]=1.0;
	    Box[3]=20.0;

	    Box[0]+=1;
	    Box[1]+=1;
		glutPostRedisplay();			// et on demande le réaffichage.
		break;

	case 114:
	    Box[2]=1.0;
        Box[3]=9.0;

        glutPostRedisplay();			// et on demande le réaffichage.
		break;

    case 116:
        Box[2]=11.0;
        Box[3]=30.0;
        glutPostRedisplay();			// et on demande le réaffichage.
		break;

	}
}

GLvoid callback_motion(int x, int y)
{
    glutPostRedisplay();
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{

	}
}

void character()
{
    ///BOTTOM/TOP
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  ///OJO
    glBindTexture(GL_TEXTURE_2D, texture5);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0,1.0,0.0);
        glVertex3d(Box[0],Box[3],Box[5]);

        glTexCoord2f(0.0, 1.0f);
        glNormal3f(0.0,1.0,0.0);
        glVertex3d(Box[1],Box[3],Box[5]);

        glTexCoord2f(1.0, 1.0f);
        glNormal3f(0.0,1.0,0.0);
        glVertex3d(Box[1],Box[3],Box[4]);

        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0,1.0,0.0);
        glVertex3d(Box[0],Box[3],Box[4]);
    glEnd();
    ///LR
    glBegin(GL_POLYGON);
        glVertex3d(Box[0],Box[2],Box[4]);
        glVertex3d(Box[0],Box[3],Box[4]);
        glVertex3d(Box[0],Box[3],Box[5]);
        glVertex3d(Box[0],Box[2],Box[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(Box[1],Box[2],Box[4]);
        glVertex3d(Box[1],Box[3],Box[4]);
        glVertex3d(Box[1],Box[3],Box[5]);
        glVertex3d(Box[1],Box[2],Box[5]);
    glEnd();
    ///FRONT/BACK
    glBegin(GL_POLYGON);
        glVertex3d(Box[0],Box[2],Box[5]);
        glVertex3d(Box[0],Box[3],Box[5]);
        glVertex3d(Box[1],Box[3],Box[5]);
        glVertex3d(Box[1],Box[2],Box[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3d(Box[0],Box[2],Box[4]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3d(Box[0],Box[3],Box[4]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3d(Box[1],Box[3],Box[4]);

        glTexCoord2f(1.0, 0.0);
        glVertex3d(Box[1],Box[2],Box[4]);
    glEnd();
}

float mov=0.01;

void floor()
{
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  ///OJO
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0+mov, 0.0);
        glVertex3d(-30,0,-200);

        glTexCoord2f(0.0+mov, 1.0f);
        glVertex3d(30,0,-200);

        glTexCoord2f(1.0+mov, 1.0f);
        glVertex3d(30,0,0);

        glTexCoord2f(1.0+mov, 0.0);
        glVertex3d(-30,0,0);
    glEnd();
    mov-=0.005;
}

void enemy1()
{
    ///BOTTOM/TOP
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(E1[0],E1[3],E1[5]);

        glTexCoord2f(0.0, 1.0f);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(E1[1],E1[3],E1[5]);

        glTexCoord2f(1.0, 1.0f);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(E1[1],E1[3],E1[4]);

        glTexCoord2f(1.0, 0.0);
        glNormal3f(0.0,1.0,0.0);
        glVertex3f(E1[0],E1[3],E1[4]);
    glEnd();
    ///LR

    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(E1[0],E1[2],E1[4]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3f(E1[0],E1[3],E1[4]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3f(E1[0],E1[3],E1[5]);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(E1[0],E1[2],E1[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(E1[1],E1[2],E1[4]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3f(E1[1],E1[3],E1[4]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3f(E1[1],E1[3],E1[5]);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(E1[1],E1[2],E1[5]);
    glEnd();
    ///FRONT/BACK

    glBegin(GL_POLYGON);
        glVertex3f(E1[0],E1[2],E1[5]);
        glVertex3f(E1[0],E1[3],E1[5]);
        glVertex3f(E1[1],E1[3],E1[5]);
        glVertex3f(E1[1],E1[2],E1[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
//        glNormal3f(1.0,0.0,0.0);
        glVertex3f(E1[0],E1[2],E1[4]);

        glTexCoord2f(0.0, 1.0f);
//        glNormal3f(1.0,0.0,1.0);
        glVertex3f(E1[0],E1[3],E1[4]);

        glTexCoord2f(1.0, 1.0f);
//        glNormal3f(1.0,0.0,1.0);
        glVertex3f(E1[1],E1[3],E1[4]);

        glTexCoord2f(1.0, 0.0);
//        glNormal3f(1.0,0.0,1.0);
        glVertex3f(E1[1],E1[2],E1[4]);
    glEnd();
}

void enemy2()
{
    glBindTexture(GL_TEXTURE_2D, texture3);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3d(E2[0],E2[2],E2[4]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3d(E2[1],E2[2],E2[4]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3d(E2[1],E2[2],E2[5]);

        glTexCoord2f(1.0, 0.0);
        glVertex3d(E2[0],E2[2],E2[5]);
    glEnd();
}

void enemy3()
{
        ///BOTTOM/TOP
    glBindTexture(GL_TEXTURE_2D, texture4);
    glBegin(GL_POLYGON);
//        glNormal3f(); /// NORMAL POR CARA
        glTexCoord2f(0.0, 0.0);
        glVertex3f(E3[0],E3[3],E3[5]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3f(E3[1],E3[3],E3[5]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3f(E3[1],E3[3],E3[4]);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(E3[0],E3[3],E3[4]);
    glEnd();
    ///LR
    glBegin(GL_POLYGON);
        glVertex3f(E3[0],E3[2],E3[4]);
        glVertex3f(E3[0],E3[3],E3[4]);
        glVertex3f(E3[0],E3[3],E3[5]);
        glVertex3f(E3[0],E3[2],E3[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(E3[1],E3[2],E3[4]);
        glVertex3f(E3[1],E3[3],E3[4]);
        glVertex3f(E3[1],E3[3],E3[5]);
        glVertex3f(E3[1],E3[2],E3[5]);
    glEnd();
    ///FRONT/BACK
    glBegin(GL_POLYGON);
        glVertex3f(E3[0],E3[2],E3[5]);
        glVertex3f(E3[0],E3[3],E3[5]);
        glVertex3f(E3[1],E3[3],E3[5]);
        glVertex3f(E3[1],E3[2],E3[5]);
    glEnd();
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(E3[0],E3[2],E3[4]);

        glTexCoord2f(0.0, 1.0f);
        glVertex3f(E3[0],E3[3],E3[4]);

        glTexCoord2f(1.0, 1.0f);
        glVertex3f(E3[1],E3[3],E3[4]);

        glTexCoord2f(1.0, 0.0);
        glVertex3f(E3[1],E3[2],E3[4]);
    glEnd();
}

int ran;
int ran_pos,ran_pos1;
bool nmi1=0;
bool nmi2=0;
bool nmi3=0;
GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,0.001,200);

    ///CAMERA ANGLES
	gluLookAt(0,30,40,0,15,0,0,1,0);

    ran=rand()%100+1;
    if(!nmi1)       ///POSICION ALEATORIA PARA NMI1
    {
        ran_pos=rand()%50+1;
        ran_pos-=30;
    }
    if(ran==4)
    {
        E1[0]=ran_pos;
        E1[1]=ran_pos+10.0;
        nmi1=1;
    }
    if(!nmi2)       ///POSICION ALEATORIA PARA NMI2
    {
        ran_pos1=rand()%50+1;
        ran_pos1-=30;
    }
    if(ran==9)
    {
        E2[0]=ran_pos1;
        E2[1]=ran_pos1+10.0;
        nmi2=1;
    }
    if(ran==5)
        nmi3=1;

    floor();
    character();

    if(nmi1)
    {
        if(nmi2)
        {
            if(Collision(E1,E2))
                cout<<"SE CHOCAN 1 y 2"<<endl;
        }
        enemy1();
        E1[4]+=1.0;
        E1[5]+=1.0;
        if(E1[5]>0)
        {
            E1[4]=-160.0;
            E1[5]=-170.0;
            nmi1=0;
        }
        if(Collision(Box,E1))
            cout<<"COLISION NMY 1"<<endl;
    }
    if(nmi2)
    {
        enemy2();
        E2[4]+=1.0;
        E2[5]+=1.0;
        if(E2[5]>0)
        {
            E2[4]=-160.0;
            E2[5]=-170.0;
            nmi2=0;
        }
        if(Collision(Box,E2))
            cout<<"COLISION NMY 2"<<endl;
    }
    if(nmi3)
    {
        enemy3();
        E3[4]+=1.0;
        E3[5]+=1.0;
        if(E3[5]>0)
        {
            E3[4]=-160.0;
            E3[5]=-170.0;
            nmi3=0;
        }
        if(Collision(Box,E3))
            cout<<"COLISION NMY 3"<<endl;
    }

    glutSpecialFunc(&callback_special);
//	glutMouseFunc(&callback_mouse);
//	glutMotionFunc(&callback_motion);


	glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,0.001,100);

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
