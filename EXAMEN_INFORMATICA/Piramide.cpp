#include "Piramide.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <thread>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
using namespace std;

void Piramide :: dibujadibujo(float _tiempo)
{
	/*Dependiendo la direccion le voy a sumar o restar a cada componente*/
	x += direccionx * _tiempo;//x=0 
	y += direcciony * _tiempo;
	z += direccionz * _tiempo;

	if (x > 5 || x < -5)
	{
		direccionx *= -1;
	}
	
	/*cout << direcciony << endl;
	if (y + direcciony < 0) {
		direcciony *= -1;
	}*/
	if (y + direcciony > 10 || y + direcciony < 0)
	{
		direcciony *= -1;
		
	}
	
	if (z + direccionz > 5 || z + direccionz < -5)
	{
		direccionz *= -1;
	}


	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(x, y, z);
	
	
	glScalef(tamano, tamano, tamano);
	
	
	 
	glBegin(GL_TRIANGLES); //cara
	
	
	glColor3f(1, 0, 1);

	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	

	glBegin(GL_TRIANGLES); //trasera
	
	glColor3f(1, 1, 1);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(0.5f, -0.5f, -1.0f);
	glEnd();


	glBegin(GL_TRIANGLES); //izquierda
	
	glColor3f(0, 0, 1);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();
	
	glBegin(GL_TRIANGLES); //derecha
	
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, 0.5f, -0.5f);
	glVertex3f(0.5f,-0.5f, -1.0f);
	glVertex3f(0.5f,-0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5f, -0.5f, -1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, -1.0f);
	glEnd();
	 

	glPopMatrix();
}
 /* 
void Piramide::colorrandom()
{
	colorr = (rand() % 100) / 100.0f;
}
  */
 


Piramide::Piramide()
{
	x = (rand() % 10) - 5;
	
	y = (rand() % 10);
	
	z = (rand() % 10) - 5;
	
	tamano = (static_cast<float>(std::rand()) / RAND_MAX) * 2 + 1;;

	direccionx = (rand() % 2);//0 -> -1 //1 -> 1 ;
	if (direccionx == 0)
	{
		direccionx = -1;
	}
	direcciony = (rand() % 2);
	if (direcciony == 0)
	{
		direcciony = -1;
	}
	direccionz = (rand() % 2);
	if (direccionz == 0)
	{
		direccionz = -1;
	}
	angle = 90;
	rotacionx = (rand() % 1);
	rotaciony = (rand() % 1);
	rotacionz = (rand() % 1);
	cout << tamano<<tamano<<tamano;


	
	
}


