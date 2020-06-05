#pragma once

#include "Cjugador.h"
#include "CFantasma.h"
#include <vector>


using namespace std;

class CVecFantasma
{
public:
	CVecFantasma();
	~CVecFantasma();
	void Agregar();
	void Dibujar(CFantasma* arrcriatira,BufferedGraphics^ buffer, Bitmap ^ img);
	void Mover(CFantasma* arrcriatira,int AnchoF, int LargoF);
	void Eliminar(CFantasma *objenem);
	void HayColision(CFantasma* arrcriatira,Cjugador * objsonic, BufferedGraphics^ buffer);
	vector<CFantasma*>*get_vectorf();

private:
	vector<CFantasma*>* arrcriatura;
};

CVecFantasma::CVecFantasma()
{
	arrcriatura = new vector<CFantasma*>();

}

CVecFantasma::~CVecFantasma()
{

}

void CVecFantasma::Agregar()
{
	CFantasma *objEnemigo = new CFantasma();
	arrcriatura->push_back(objEnemigo);
}

void CVecFantasma::Dibujar(CFantasma* arrcriatira ,BufferedGraphics^ buffer, Bitmap ^ img)
{
	
	arrcriatira->Dibujar(buffer, img);	
	
}

void CVecFantasma::Mover(CFantasma* arrcriatira,int AnchoF, int LargoF)
{
	
	arrcriatira->Mover(AnchoF, LargoF);
	
}

void CVecFantasma::Eliminar(CFantasma *objenem)
{
	if (objenem->Get_Estado() == false)
	{
		objenem->borrar();
	}
}
void CVecFantasma::HayColision(CFantasma* arrcriatira, Cjugador * objsonic,BufferedGraphics^ buffer)
{
	
	if (arrcriatira->Get_Estado() && arrcriatira->HayColision(objsonic->Get_X(), objsonic->Get_Y(), objsonic->Get_Ancho(), objsonic->Get_Largo()) ||
		objsonic->HayColision(arrcriatira->Get_x(), arrcriatira->Get_y(), arrcriatira->Get_Ancho(), arrcriatira->Get_Largo()))
	{
		objsonic->Set_MonedasRecogidas(0);
		objsonic->Animacion_Daño();
		arrcriatira->Set_Estado(false);
		Eliminar(arrcriatira);
	}
}

vector<CFantasma*>* CVecFantasma::get_vectorf()
{
	return arrcriatura;
}

