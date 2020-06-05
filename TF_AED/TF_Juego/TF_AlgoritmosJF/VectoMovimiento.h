#pragma once
#include"CLista.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class VectoMovimiento 
{
protected:
	int x;
	int y;
	int aux;
	int anchoF;
	int altoF;
	int posx;
	int posy;
	SLista<Bitmap^> vecmo;
public:
	VectoMovimiento() 
	{
		x = 0;
		y = 0;
		aux = 0;
		anchoF = 0;
		altoF = 0;
		posx = 0;
		posy = 0;
	}

	virtual void DibujarVectoMovimiento(Graphics^g, Bitmap^img, int ancho, int alto, Keys Mov) = 0;
	void Set_x(int x) 
	{
		this->x = x;
	}
	int Get_x() 
	{
		return x;
	};
};