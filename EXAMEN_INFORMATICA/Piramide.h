#pragma once
class Piramide
{
public:
	float Colores;
	float angle;
	float x, y, z;
	int tamano;
	float direccionx;
	float direcciony;
	float direccionz;
	int rotacionx;
	int rotaciony;
	int rotacionz;
	float r;
	float g;
	float b;
	float cara1;
	void dibujadibujo(float _tiempo);
	void colorrandom();
	Piramide();
};


