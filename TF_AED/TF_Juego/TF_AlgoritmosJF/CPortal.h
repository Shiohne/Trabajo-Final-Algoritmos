
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace std;

class CPortal
{
private:
	bool Estado;
	int X;
	int Y;
	int ancho;
	int largo;
	int indice_i;
	int indice_j;
public:
	CPortal(int X, bool estado)
	{
		this->X = X;
		this->Y = 205;
		this->Estado = estado;
		ancho = 46;
		largo = 68;
		indice_i = 0;
		indice_j = 0;
	}
	~CPortal();

	void dibujarPortal(Bitmap^ Img_Portal, BufferedGraphics^buffer)
	{
		if (Estado == false)
		{
			indice_i = 0;
			indice_j = 0;
		}
		else
		{
			indice_j = 1;
		}
		Rectangle Frame = Rectangle(indice_i*ancho, indice_j*largo, ancho, largo);
		Rectangle Pantalla = Rectangle(X, Y, 3*ancho, 3*largo);

		buffer->Graphics->DrawImage(Img_Portal, Pantalla, Frame, GraphicsUnit::Pixel);
		if (indice_j == 1)
		{
			if (indice_i == 5)
			{
				indice_i = 0;
			}
			else
			{
				indice_i++;
			}
		}
		
	}
	bool Get_Estado()
	{
		return Estado;
	}
	void Set_Estado(bool est)
	{
		this->Estado = est;
	}
	int Get_X()
	{
		return X;
	}
	void Set_X(int x)
	{
		X = x;
	}
};
