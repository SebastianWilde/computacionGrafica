#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include <math.h>       /* cos */
#define KEY_ESC 27

#include <iostream>
using namespace std;
#define PI 3.14159
//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(1, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 1);
	glEnd();
}

//dibujar cuadrado
void drawSquare(int cx,int cy, int tam_arista)
{
    /*parametros*/
    /*Dibujo*/
    glBegin(GL_LINE_LOOP);
    glColor3d(255,0,0);
    glVertex2f((GLfloat)cx+tam_arista/2,(GLfloat)cy+tam_arista/2);//left of window
    glVertex2f((GLfloat)cx-tam_arista/2,(GLfloat)cy+tam_arista/2);//bottom of window
    glVertex2f((GLfloat)cx-tam_arista/2,(GLfloat)cy-tam_arista/2);//right of window
    glVertex2f((GLfloat)cx+tam_arista/2,(GLfloat)cy-tam_arista/2);//top of window
    glEnd();
}

//Dibujar un circulo
void drawCircle(int cx, int cy, int radio)
{
    glBegin(GL_LINES);
    glColor3d(255,0,0);
    float x,y;
    for (double i= 0.0;i<20;i+=0.001)
    {
        x = cx + radio * cos(i);
        y = cy + radio * sin(i);
        glVertex2f(x,y);
    }
    glEnd();
}

//funcion circulos dentro de otros
void drawCircles1(int n_circulos, int reduccion, int cx, int cy, int radio)
{
    int newRadio;
    for (int i = 0, p = 0; i < n_circulos && p<100; i++,p+=reduccion)
    {
        newRadio = radio - (radio * p /100);;
        drawCircle(cx-(radio-newRadio),cy,newRadio);
    }
}
//funcion circulos consecutivos
void drawCirclesC(int n_circulos, int reduccion, int cx, int cy, int radio)
{
    drawCircle(cx,cy,radio);
    int red = radio*reduccion/100;
    for (int i = 1, p = reduccion; i < n_circulos && p<100; i++,p+=reduccion)
    {
        cx+=radio;
        radio -= red;
        cx+=radio;
        drawCircle(cx,cy,radio);
    }
}

//funcion circulos consecutivos 2
void drawCirclesC2(int n_circulos, int reduccion,int angulo, float cx, float cy, int radio)
{
    drawCircle(cx,cy,radio);
    int red = radio*reduccion/100;
    float cosAngulo = cos(angulo*PI/180);
    float sinAngulo = sin(angulo*PI/180);
    int newRadio;
    cout<<"cx "<<cosAngulo<<" cy "<<sinAngulo<<endl;
    for (int i = 1, p = reduccion; i < n_circulos && p<100; i++,p+=reduccion)
    {
        newRadio = radio - red;
        cx+=cosAngulo*(radio+newRadio);
        cy+=sinAngulo*(radio+newRadio);
        drawCircle(cx,cy,newRadio);
        radio=newRadio;
    }
}
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
//	displayGizmo();

	drawSquare(-40,40,10);
	drawCircle(40,40,10);
    drawCircles1(5,10,0,40,10);
    drawCirclesC(5,20,-30,15,10);
    drawCirclesC2(5,20,30,0,-20,10);
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}

