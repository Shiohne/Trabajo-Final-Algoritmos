#pragma once
#include <iostream>
#include <ctime>
#define NFRAMESS 16

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

class CMonedas
{
private:
	int X, Y;
	int Ancho;
	int Largo;
	int Indice;
	bool Estado;


public:
	CMonedas();
	~CMonedas();
	void Dibujar(BufferedGraphics^ buffer, Bitmap^ img);
	bool HayColision(int pX, int pY);
	bool HayColision(int pX, int pY, int pAncho, int pLargo);
	int Get_x();
	int Get_y();
	int Get_Ancho();
	int Get_Largo();
	void Set_X(int X);
	bool Get_Estado();
	void Set_Estado(bool Estado);
	void borrar();
};


CMonedas::CMonedas()
{
	this->X = rand() % 1750 + 100;
	this->Y = rand()%230+100;
	this->Ancho = 50;
	this->Largo = 50;
	this->Indice = 0;
	this->Estado = true;
}

CMonedas ::~CMonedas() {}
void CMonedas::Dibujar(BufferedGraphics^ buffer, Bitmap^ img)
{
	int AnchoI = img->Width / NFRAMESS;
	int LargoI = img->Height;
	Rectangle Origen = Rectangle(Indice * AnchoI, 0, AnchoI, LargoI);
	Rectangle Destino = Rectangle(X, Y, Ancho, Largo);
	buffer->Graphics->DrawImage(img, Destino, Origen, GraphicsUnit::Pixel);
	if (Indice == NFRAMESS - 1)
		Indice = 0;
	else
		Indice++;
}


bool CMonedas::HayColision(int pX, int pY)
{
	return pX >= X && pX <= X + Ancho && pY >= Y && pY <= Y + Largo;
}

bool CMonedas::HayColision(int pX, int pY, int pAncho, int pLargo)
{
	return HayColision(pX, pY) || HayColision(pX + pAncho, pY) || HayColision(pX, pY + pLargo) || HayColision(pX + pAncho, pY + pLargo);
}

int CMonedas::Get_x()
{
	return this->X;
}

int CMonedas::Get_y()
{
	return this->Y;
}

int CMonedas::Get_Ancho()
{
	return this->Ancho;
}

int CMonedas::Get_Largo()
{
	return this->Largo;
}

void CMonedas::Set_X(int X)
{
	this->X = X;
}

bool CMonedas::Get_Estado()
{
	return this->Estado;
}

void CMonedas::Set_Estado(bool Estado)
{
	this->Estado = Estado;
}
void CMonedas::borrar()
{
	Largo = NULL;
	Ancho = NULL;
	X = NULL;
	Y = NULL;
}