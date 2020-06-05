#pragma once
#include <ctime>
#include "Monedas.h"
#include <iostream>
#include <vector>
#include "CVecFantasma.h"
#include "Juego_go.h"
#include "HashMap.h"
#include "CPortal.h"
#include "CFantasma.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

class CMapa
{
private:
	int X;
	int dX;
	int Nro;
	int Indice;
	int Ancho;
	int Largo;
	int NroMonedas;
	int MonedasParaActivarPortal;
	Keys tecla;
	
	int AnchoPantalla;
	int LargoPantalla;

	bool MapaLimiteIzquierda;
	bool MapaLimiteDerecha;
	bool MovimientoMapa;
	CVecFantasma* VecFantasmas;
	HashMap<CFantasma*>* HHFantasma;
	vector<CMonedas*>* ArrMonedas;
	CPortal* PortalSiguiente;
	CPortal* PortalAnterior;
	CFantasma* fantasma1;
public:
	CMapa(int nro, CVecFantasma* vfantasma, HashMap<CFantasma*>* HFantasma)
	{
		srand(time(NULL));
		X = 0;
		dX = 8;
		Nro = nro;
		Indice = rand() % 5;
		Ancho = 511;
		Largo = 249;
		tecla = Keys::None;
		AnchoPantalla = 1022;
		LargoPantalla = 490;
		VecFantasmas = vfantasma;
		HHFantasma = HFantasma;
		MovimientoMapa = true;
		PortalAnterior = new CPortal(0, true);
		PortalSiguiente = new CPortal(1850, false);
		MonedasParaActivarPortal = 10;
		ArrMonedas = new vector<CMonedas*>();
		NroMonedas = 15;
		for (int i=0; i < NroMonedas; i++)
		{
			CMonedas *newMoneda = new CMonedas();
			ArrMonedas->push_back(newMoneda);
		}
		fantasma1 = new CFantasma();
	}
	~CMapa();

	void dibujarMapa(Bitmap^ Img_Mapa, Bitmap^Img_moneda, Bitmap^Img_portal, BufferedGraphics^buffer, Cjugador * pj)
	{
		Rectangle OrigenMapa = Rectangle(X, Indice*Largo, Ancho, Largo);
		Rectangle PantallaMapa = Rectangle(0, 0, AnchoPantalla, LargoPantalla);

		Rectangle OrigenMoneda = Rectangle(0, 0, 60, 64);
		Rectangle PantallaMoneda = Rectangle(809, 17, 40, 40);

		buffer->Graphics->DrawImage(Img_Mapa, PantallaMapa, OrigenMapa, GraphicsUnit::Pixel);
		buffer->Graphics->DrawString("Nivel "+ Nro.ToString(), gcnew System::Drawing::Font("OCR-A BT", 31), Brushes::Black, 33, 13);
		buffer->Graphics->DrawString("Nivel " + Nro.ToString(), gcnew System::Drawing::Font("OCR-A BT", 30), Brushes::WhiteSmoke, 30, 10);
		buffer->Graphics->DrawString("Work in Progress", gcnew System::Drawing::Font("OCR-A BT", 20), Brushes::WhiteSmoke, 700, 440);

		buffer->Graphics->DrawImage(Img_moneda, PantallaMoneda, OrigenMoneda, GraphicsUnit::Pixel);
		buffer->Graphics->DrawString(" x " + pj->Get_MonedasRecogidas().ToString(), gcnew System::Drawing::Font("OCR-A BT", 31), Brushes::Black, 843, 13);
		buffer->Graphics->DrawString(" x " + pj->Get_MonedasRecogidas().ToString(), gcnew System::Drawing::Font("OCR-A BT", 30), Brushes::WhiteSmoke, 840, 10);
		PortalSiguiente->dibujarPortal(Img_portal, buffer);
		buffer->Graphics->DrawString(MonedasParaActivarPortal.ToString(), gcnew System::Drawing::Font("OCR-A BT", 15), Brushes::LightGray, PortalSiguiente->Get_X()+50, 269);
		if (pj->Get_Tiempo() > -100)
		{
			buffer->Graphics->DrawString("Tiempo: ", gcnew System::Drawing::Font("OCR-A BT", 31), Brushes::Black, 453, 13);
			buffer->Graphics->DrawString("Tiempo: ", gcnew System::Drawing::Font("OCR-A BT", 30), Brushes::White, 450, 10);
			buffer->Graphics->DrawString(pj->Get_Tiempo().ToString(), gcnew System::Drawing::Font("OCR-A BT", 31), Brushes::Black, 653, 13);
			buffer->Graphics->DrawString(pj->Get_Tiempo().ToString(), gcnew System::Drawing::Font("OCR-A BT", 30), Brushes::White, 650, 10);
		}
		for (int i = 0; i < ArrMonedas->size(); i++)
		{
			ArrMonedas->at(i)->Dibujar(buffer, Img_moneda);
		}
		if (Nro != 1)
		{
			PortalAnterior->dibujarPortal(Img_portal, buffer);
		}
	}
	vector<CMonedas*>* getarrmoneda()
	{
		return ArrMonedas;
	}
	void MoverMapa(Cjugador*pj)
	{
		if (pj->Get_MonedasRecogidas() >= MonedasParaActivarPortal)
		{
			PortalSiguiente->Set_Estado(true);
		}
		if (pj->Get_X() == 435 && pj->Get_Indice_j() != 3)
		{
			MovimientoMapa = true;
			if (tecla == Keys::Right)
			{
				if (X + Ancho + dX <= 1021)
				{
					PortalAnterior->Set_X(PortalAnterior->Get_X() - 2 * dX);
					PortalSiguiente->Set_X(PortalSiguiente->Get_X() - 2 * dX);
					for (int i = 0; i < NroMonedas; i++)
					{
						ArrMonedas->at(i)->Set_X(ArrMonedas->at(i)->Get_x() - 2 * dX);
					}
					if (Nro == HHFantasma->get_key(Nro))
					{
						for (int i = 0; i < VecFantasmas->get_vectorf()->size(); i++)
						{
							if (VecFantasmas->get_vectorf()->at(i) == HHFantasma->get(Nro))
							{
								VecFantasmas->get_vectorf()->at(i)->Set_X(VecFantasmas->get_vectorf()->at(i)->Get_x() - 2 * dX);
							}
						}
					}
					
					X += dX;
				}
				else
				{
					MovimientoMapa = false;
				}
			}

			if (tecla == Keys::Left)
			{
				if (X - dX >= 0)
				{
					PortalAnterior->Set_X(PortalAnterior->Get_X() + 2 * dX);
					PortalSiguiente->Set_X(PortalSiguiente->Get_X() + 2 * dX);
					for (int i = 0; i < NroMonedas; i++)
					{
						ArrMonedas->at(i)->Set_X(ArrMonedas->at(i)->Get_x() + 2 * dX);
					}
					if (Nro == HHFantasma->get_key(Nro))
					{
						for (int i = 0; i < VecFantasmas->get_vectorf()->size(); i++)
						{
							if (VecFantasmas->get_vectorf()->at(i) == HHFantasma->get(Nro))
							{
								VecFantasmas->get_vectorf()->at(i)->Set_X(VecFantasmas->get_vectorf()->at(i)->Get_x() + 2 * dX);
							}
						}
					}
					X -= dX;
				}
				else
				{
					MovimientoMapa = false;
				}
			}
		}
	}

	void EliminarMonedas(CMonedas*objMoneda)
	{
		if (objMoneda->Get_Estado() == false)
		{
			objMoneda->borrar();
		}
	}
	void HayColision_Moneda(Cjugador * objsonic)
	{
		for (int i = 0; i < ArrMonedas->size(); i++)
		{
			if (ArrMonedas->at(i)->Get_Estado() && ArrMonedas->at(i)->HayColision(objsonic->Get_X(), objsonic->Get_Y(), objsonic->Get_Ancho(), objsonic->Get_Largo()) ||
				objsonic->HayColision(ArrMonedas->at(i)->Get_x(), ArrMonedas->at(i)->Get_y(), ArrMonedas->at(i)->Get_Ancho(), ArrMonedas->at(i)->Get_Largo()))
			{
				ArrMonedas->at(i)->Set_Estado(false);
				EliminarMonedas(ArrMonedas->at(i));
				objsonic->Set_MonedasRecogidas(objsonic->Get_MonedasRecogidas() + 1);
				objsonic->aumentartiempo();
			}
		}
	}

	void set_vecfantasma(CVecFantasma* vfantasma)
	{
		VecFantasmas = vfantasma;
	}
	void set_H_fantasma(HashMap<CFantasma*>* HFantasma)
	{
		HHFantasma = HFantasma;
	}
	int Get_Nro()
	{
		return Nro;
	}
	void Set_tecla(Keys tecla)
	{
		this->tecla = tecla;
	}
	int Get_X()
	{
		return X;
	}
	bool Get_MovimientoMapa()
	{
		return MovimientoMapa;
	}
	void Set_MovimientoMapa(bool mov)
	{
		MovimientoMapa = mov;
	}
	void Set_MonedasParaActivarPortal(int monedas)
	{
		MonedasParaActivarPortal = monedas;
	}
	int Get_MonedasParaActivarPortal()
	{
		return MonedasParaActivarPortal;
	}
	CPortal* Get_PortalSiguiente()
	{
		return PortalSiguiente;
	}
};
