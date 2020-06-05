#pragma once
#include <iostream>
#include <fstream>
#include<iomanip>
#include <string>
#include <vector>
#include "CMapa.h"
#include "Cjugador.h"
#include "CLista.h"
#include "Animaciones.h"
#include "Menu.h"
#include "CFantasma.h"
#include "HashMap.h"
#include "CVecFantasma.h"
using namespace std;

class Juego_go {
private:
	CMapa * mapa;
	Cjugador* pj;
	CMenu * menu;
	Animaciones* animaciones;
	Lista<CMapa*>* ListaMapas;
	HashMap<CFantasma*>* HFantasma;
	CVecFantasma* vfantasma;

	bool Spawneando;
	bool GameOver;
	int timer_ticks;

public:
	Juego_go() 
	{
		GameOver = false;
		pj = new Cjugador();
		menu = new CMenu();
		animaciones = new Animaciones();
		vfantasma = new CVecFantasma();
		HFantasma = new HashMap<CFantasma*>();
		
		for (int i = 0; i < 5000; i++)
		{
			vfantasma->Agregar();
		}
		for (int i = 0; i <5000; i++)
		{
			HFantasma->Hash(5, vfantasma->get_vectorf()->at(i));
		}
		mapa = new CMapa(1, vfantasma,HFantasma);
		ListaMapas = new Lista<CMapa*>();
		ListaMapas->agregaInicial(mapa);
		timer_ticks = 0;
		Spawneando = true;
	}
	void EmpezarJuego(Bitmap^Img_menu1, Bitmap^Img_menu2, Bitmap^Img_Mapa, Bitmap^Img_Sonic, Bitmap^Img_Fantasma, Bitmap^Img_moneda, Bitmap^Img_portal, Bitmap^Img_Ready, BufferedGraphics^buffer, int AnchoForm, int LargoForm)
	{
		if (menu->Get_GameStart() == false)
		{
			menu->DibujarMenu(Img_menu1, Img_menu2, buffer, AnchoForm, LargoForm);
		}
		else
		{
			timer_ticks++;
			mapa->dibujarMapa(Img_Mapa, Img_moneda,Img_portal, buffer,pj);
			if (timer_ticks <= 35)
			{
				animaciones->Animacion_Ready(Img_Ready, buffer, timer_ticks);
			}
			else
			{
				pj->DibujarPersonaje(Img_Sonic, buffer);
			}
			if (timer_ticks > 35 && pj->Get_X() < 435 && Spawneando == true)
			{
				pj->Animacion_entrada();
			}
			if (pj->Get_X() == 435 && Spawneando == true)
			{
				pj->ResetPJ();
				if (pj->Get_Tiempo() >0 )
				{
					Spawneando = false;
				}
				else
				{
				
					Spawneando = true;
				}
				
				
			}
			if (Spawneando == false)//Inicia el Juego
			{
				ImprimeFantasma(Img_Fantasma, buffer, pj, AnchoForm, LargoForm);
				mapa->MoverMapa(pj);
				pj->Movimiento(AnchoForm, LargoForm, mapa->Get_MovimientoMapa());
				mapa->HayColision_Moneda(pj);
				if (pj->Get_Tiempo() <= 0 )
				{
					timer_ticks = 0;
					GameOver = true;
					Spawneando = true;

					const char* filename = "records.txt";
					GuardarScore((char*)filename);
				}
			}
			if (GameOver == true)
			{
				timer_ticks++;
				pj->Animacion_Muere(timer_ticks);
			}
		}

	}
	
	void ImprimeFantasma(Bitmap^Img_Fantasma, BufferedGraphics^buffer, Cjugador* pe, int AnchoForm, int LargoForm)
	{
		if (mapa->Get_Nro() == HFantasma->get_key(mapa->Get_Nro()))
		{
			for (int i = 0; i < vfantasma->get_vectorf()->size(); i++)
			{
				if (vfantasma->get_vectorf()->at(i) == HFantasma->get(mapa->Get_Nro()))
				{
					vfantasma->Dibujar(HFantasma->get(mapa->Get_Nro()), buffer, Img_Fantasma);
					vfantasma->Mover(HFantasma->get(mapa->Get_Nro()), AnchoForm, LargoForm);
					vfantasma->HayColision(HFantasma->get(mapa->Get_Nro()), pe, buffer);
				}
			}
		}
	}
	void PresionaTecla(Keys tecla)
	{
		menu->Tecla(tecla);
		if (Spawneando == false)
		{
			mapa->Set_tecla(tecla);
			pj->Animacion(tecla);
		}
	}
	void CambiarMapa()
	{
		if (pj->Get_LimiteDerecha() == true && mapa->Get_PortalSiguiente()->Get_Estado() == true)
		{
			if (mapa->Get_Nro() == ListaMapas->longitud())
			{
				CMapa * NuevoMapa = new CMapa(ListaMapas->longitud() + 1, vfantasma,HFantasma);
				NuevoMapa->Set_MonedasParaActivarPortal(mapa->Get_MonedasParaActivarPortal() + 10);
				ListaMapas->agregaFinal(NuevoMapa);
			}
			mapa = ListaMapas->obtenerPos(mapa->Get_Nro());
			pj->ResetPosicion();
		}
		else if (pj->Get_LimiteIzquierda() == true && mapa->Get_Nro() != 1)
		{
			mapa = ListaMapas->obtenerPos(mapa->Get_Nro() - 2);
			pj->ResetPosicion();
		}
		mapa->Set_MovimientoMapa(false);
		
	}
	bool Get_GameOver()
	{
		return GameOver;
	}
	int Get_Timerticks()
	{
		return timer_ticks;
	}
	void GuardarScore(char* filename)
	{
		ofstream out;
		out.open(filename);
		if (out.good()) { // Make sure the file was opened properly
			out << pj->Get_MonedasRecogidas() << " "; // Space delimited
			out << endl;
			out.close();
		}
		else
			cout << "Unable to save the file" << endl;
	}
};