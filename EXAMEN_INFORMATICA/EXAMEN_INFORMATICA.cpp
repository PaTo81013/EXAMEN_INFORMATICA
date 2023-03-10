#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Piramide.h"

using namespace std;

//Variables  para contar el tiempo
int t = 1, old_t = 1;
float dt = 0;
float angle = 0;
float speed = 30;


float slider = 0;
float amplitud = 50;
bool goingLeft = false, goingRight = false;
const int nPedos = 10;

Piramide pedos[nPedos];


#pragma region OpenGLSetupInputAndStuff

void changeWindowSize(int w, int h)
{
	cout << "redim" << endl;
	// Previene una división por cero, cuando la ventana es demasiado corta
	// (no puede haber ventana con 0 de ancho).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Usa la matriz de proyección
	glMatrixMode(GL_PROJECTION);

	// Reinicia Matriz
	glLoadIdentity();

	// Hace que el Viewport use toda la pantalla
	glViewport(0, 0, w, h);

	// da la perspectiva correcta, fov, ratio, nearClip, farClip
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// usa la matriz de modelos the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Initialization() {
	cout << "Codigo inicial aqui" << endl;
}
void crearbase()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //cara inferior
	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glEnd();
	glPopMatrix();

}

void Cara()
{
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.0f, 5.0f, 5.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f); //cara trasera

	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.0f, 5.0f, -5.0f);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f); //cara frontal

	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glTranslatef(0.0f, 10.0f, 0.0f); //ARRIBA
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glEnd();
	glPopMatrix();

}


void renderScene(void)
{
	// Limpia los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reinicia las trasnformaciones
	glLoadIdentity();

	gluLookAt(
		(sin(slider) * amplitud), 10, (cos(slider) * amplitud), //pos
		0.0f, 5.0f, 0, //target
		0.0f, 1.0f, 0.0f); //up Vector


	t = glutGet(GLUT_ELAPSED_TIME); //Obteniendo el tiempo y el delta
	dt = (t - old_t) / 1000.0f;
	old_t = t;

	if (goingLeft) slider -= dt * 5;
	if (goingRight) slider += dt * 5;

	crearbase();
	Cara();
	/*for (int pedos = 3; pedos<3; pedos++)
	{
		//Piramide();
	}*/
	for (int i = 0; i < nPedos; i++)
	{
		glPushMatrix();
	    glRotatef(90*t/1000,pedos[i].rotacionx, pedos[i].rotaciony, pedos[i].rotacionz);
		pedos[i].dibujadibujo(dt);
		glPopMatrix();
	}

	glutSwapBuffers(); //intercambia los búferes de la ventana actual si tiene doble búfer.
}

void processNormalKeys(unsigned char key, int x, int y)
{
	//cout << (int)key << endl;
	if (key == 27)
		exit(0);
}

void InputDown(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT://GLUT_KEY_UP:	
		goingRight = true;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = true;
		break;
	}
}
void InputUp(int key, int xx, int yy)
{

	switch (key)
	{
	case GLUT_KEY_RIGHT:
		goingRight = false;
		break;
	case GLUT_KEY_LEFT:
		goingLeft = false;
		break;
	}
}
#pragma endregion

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1600, 900); //dimensiones
	glutCreateWindow("TemplateWindow");
	Initialization();

	// register callbacks
	glutDisplayFunc(renderScene); //establece el callback de visualización para la ventana actual. 
	glutReshapeFunc(changeWindowSize); //establece el callback de redimensionado para la ventana actual
	glutIdleFunc(renderScene); //establece el callback global de inactividad.(si no recibe eventos, resize, etc)
	glutKeyboardFunc(processNormalKeys);//las teclas ASCII
	//glutKeyboardUpFunc(processNormalKeys); 
	glutSpecialFunc(InputDown); //teclas especiales
	glutSpecialUpFunc(InputUp); //teclas especiales al soltarse	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// entrar GLUT al ciclo de procesamiento de eventos
	glutMainLoop();

	return 1;
}