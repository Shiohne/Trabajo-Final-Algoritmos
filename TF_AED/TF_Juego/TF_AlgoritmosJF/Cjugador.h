#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class Cjugador
{
private:
	int X, Y;
	int Ancho, Largo;
	int dX, dY;
	int Gravedad;

	int Indice_i;
	int Indice_j;
	int N_Frames;
	int Direccion;
	int MonedasRecogidas;
	
	bool Saltando;
	bool LimiteDerecha;
	bool LimiteIzquierda;
	int Suelo;

	int Tiempo;
	int TiempoTotal;

	Keys tecla;

public:
	~Cjugador();
	Cjugador()
	{
		X = -15;
		Y = 330;
		Ancho = 30;
		Largo = 40;
		dX = 15;
		dY = 60;
		Gravedad = 10;

		Indice_i = 0;
		Indice_j = 2;
		N_Frames = 5;
		Direccion = 1;
		
		MonedasRecogidas = 0;

		Tiempo = 167;

		Saltando = false;
		LimiteDerecha = false;
		LimiteIzquierda = false;
		
		Suelo = Y;
		tecla = Keys::None;
		
	}
	void Movimiento(int AnchoF, int LargoF, bool MovimientoMapa)
	{
		if (Saltando == true)
		{
			N_Frames = 5;
			Indice_j = 2;
			Y -= dY;
			dY -= Gravedad;

			if (Y >= Suelo)
			{
				Saltando = false;
				Indice_j = 0;
				dY = 60;
			}	
		}

		if (MovimientoMapa == false && Indice_j != 3)
		{
			if (tecla == Keys::Right)
			{
				if (X + Ancho + 6*dX <= AnchoF)
				{
					X += dX;
				}
				else
				{
					LimiteDerecha = true;
				}
			}

			if (tecla == Keys::Left)
			{
				if (X - dX >= 15)
				{
					X -= dX;
				}
				else
				{
					LimiteIzquierda = true;
				}
			}
		}
	}
	void DibujarPersonaje(Bitmap^ Img_sonic, BufferedGraphics^buffer)
	{
		Tiempo--;
		TiempoTotal = Tiempo * 6 / 100;

		Rectangle Frame;
		if (Indice_j == 2)
		{
			Indice_j = 2;
		}
		if (Direccion == -1)
		{
			Frame = Rectangle((Indice_i+1) * Ancho, Indice_j * Largo, Ancho*Direccion, Largo);
		}
		else
		{
			Frame = Rectangle(Indice_i * Ancho, Indice_j * Largo, Ancho*Direccion, Largo);
		}
		Rectangle Pantalla = Rectangle(X, Y, 3*Ancho, 3*Largo);
		buffer->Graphics->DrawImage(Img_sonic, Pantalla, Frame, GraphicsUnit::Pixel);

		
		if (Indice_i == N_Frames - 1)
		{
			if (Indice_j == 3)
			{
				Indice_j = 0;
			}
			Indice_i = 0;
		}
		else if(Indice_j != 4)
		{
			Indice_i++;
		}

		
	}

	void Animacion(Keys Tecla)
	{
		tecla = Tecla;
		if (Indice_j != 3)
		{
			if (tecla == Keys::Right && Saltando == false)
			{
				N_Frames = 8;
				Indice_j = 1;

				Direccion = 1;
				return;
			}
			else if (tecla == Keys::Left && Saltando == false)
			{
				N_Frames = 8;
				Indice_j = 1;

				Direccion = -1;
				return;
			}
			else if (tecla == Keys::Up || tecla == Keys::Space)
			{
				Saltando = true;
				N_Frames = 5;
				Indice_i = 0;
				Indice_j = 2;
				return;
			}
			else if (tecla == Keys::None)
			{
				Indice_j = 0;
			}
		}
	}

	void ResetPosicion()
	{
		if (LimiteDerecha == true)
		{
			ResetPJ();
			X = 120;
			Direccion = 1;
			LimiteDerecha = false;
		}
		else if (LimiteIzquierda == true)
		{
			ResetPJ();
			X = 780;
			Direccion = -1;
			LimiteIzquierda = false;
		}
	}
	void Animacion_Daño()
	{
		N_Frames = 8;
		Indice_j = 3;
		Indice_i = 0;
	}
	void Animacion_entrada()
	{
		X += 3*dX;
		N_Frames = 5;
		Indice_j = 2;
	}
	void Animacion_Muere(int timer_ticks)
	{
		Indice_j = 4;
		if (timer_ticks <= 20)
		{
			Indice_i = 0;
		}
		else if (timer_ticks >20 && timer_ticks <= 40)
		{
			Indice_i = 1;
		}
	}
	void ResetPJ()
	{
		X = 435;
		Y = 300;
		Ancho = 30;
		Largo = 40;
		dX = 15;
		dY = 60;
		Gravedad = 10;
		Indice_i = 0;
		Indice_j = 0;
		N_Frames = 8;
		Direccion = 1;
		Saltando = false;
		LimiteDerecha = false;
		LimiteIzquierda = false;
		Suelo = Y;
		tecla = Keys::None;
	}

	
	int Get_X()
	{
		return this->X;
	}
	int Get_Y()
	{
		return this->Y;
	}
	int Get_Ancho()
	{
		return this->Ancho;
	}
	int Get_Largo()
	{
		return this->Largo;
	}

	bool Get_LimiteDerecha()
	{
		return LimiteDerecha;
	}
	bool Get_LimiteIzquierda()
	{
		return LimiteIzquierda;
	}

	void Set_X(int X)
	{
		this->X = X;
	}
	void Set_Y(int Y)
	{
		this->Y = Y;
	}
	void Set_Indice_i(int i)
	{
		Indice_i = i;
	}
	void Set_Indice_j(int j)
	{
		Indice_j = j;
	}
	int Get_Indice_j()
	{
		return Indice_j;
	}
	void Set_N_frames(int n)
	{
		N_Frames = n;
	}
	int Get_Tiempo() 
	{
		return TiempoTotal;
	}

	bool HayColision(int pX, int pY)
	{
		return pX >= X && pX <= X + Ancho && pY >= Y && pY <= Y + Largo;
	}
	bool HayColision(int pX, int pY, int pAncho, int pLargo)
	{
		return HayColision(pX, pY) || HayColision(pX + pAncho, pY) || HayColision(pX, pY + pLargo) || HayColision(pX + pAncho, pY + pLargo);
	}
	void Set_MonedasRecogidas(int monedas)
	{
		MonedasRecogidas = monedas;
	}
	int Get_MonedasRecogidas()
	{
		return MonedasRecogidas;
	}

	void aumentartiempo()
	{
		Tiempo += 50;
	}

	void disminuirtiempo()
	{
		Tiempo -= 667;
	}
	int Get_direccion()
	{
		return Direccion;
	}
};
