#pragma once
#include <ctime>

#define NFRAMES 8

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class CFantasma
{
private:
	int X, Y;
	int Ancho, Largo;
	int dX;
	int Indice;
	bool Estado;
	int Direccion;

public:
	CFantasma();
	~CFantasma();
	void Dibujar(BufferedGraphics^ g, Bitmap^ img);
	void Mover(int AnchoF, int LargoF);
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

CFantasma::CFantasma()
{
	this->X = 900;
	this->Y = 330;
	this->Ancho = 50;
	this->Largo = 50;
	this->dX = -5;
	this->Indice = 0;
	this->Estado = true;
	Direccion = 1;
}

CFantasma ::~CFantasma() {}
void CFantasma::Dibujar(BufferedGraphics^ buffer, Bitmap^ img)
{
	Rectangle Origen;
	int AnchoI = img->Width / NFRAMES;
	int LargoI = img->Height;

	if (Direccion == -1)
	{
		Origen = Rectangle((Indice+1) * AnchoI, 0, AnchoI*Direccion, LargoI);
	}
	else
	{
		Origen = Rectangle(Indice * AnchoI,0, AnchoI*Direccion, LargoI);
	}

	Rectangle Destino = Rectangle(X, Y, 1.5*Ancho, 1.5*Largo);
	buffer->Graphics->DrawImage(img, Destino, Origen, GraphicsUnit::Pixel);

	if (Indice == NFRAMES - 1)
		Indice = 0;
	else
		Indice++;
}

void CFantasma::Mover(int AnchoF, int LargoF)
{
	if (X + dX < 0 || X + Ancho + dX > AnchoF)
	{
		dX *= -1;
		Direccion *= -1;
	}
	X += dX;
}


bool CFantasma::HayColision(int pX, int pY)
{
	return pX >= X && pX <= X + Ancho && pY >= Y && pY <= Y + Largo;
}

bool CFantasma::HayColision(int pX, int pY, int pAncho, int pLargo)
{
	return HayColision(pX, pY) || HayColision(pX + pAncho, pY) || HayColision(pX, pY + pLargo) || HayColision(pX + pAncho, pY + pLargo);
}

int CFantasma::Get_x()
{
	return this->X;
}

int CFantasma::Get_y()
{
	return this->Y;
}

int CFantasma::Get_Ancho()
{
	return this->Ancho;
}

int CFantasma::Get_Largo()
{
	return this->Largo;
}


void CFantasma::Set_X(int X)
{
	this->X = X;
}

bool CFantasma::Get_Estado()
{
	return this->Estado;
}

void CFantasma::Set_Estado(bool Estado)
{
	this->Estado = Estado;
}
void CFantasma::borrar()
{
	Largo = NULL;
	Ancho = NULL;
	X = NULL;
	Y = NULL;
}