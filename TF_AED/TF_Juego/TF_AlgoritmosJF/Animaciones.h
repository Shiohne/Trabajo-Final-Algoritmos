#include <iostream>
using namespace std;

class Animaciones
{

private:
	int X_ready;
	int i_ready;
public:
	Animaciones()
	{
		X_ready = -500;
		i_ready = 0;
	}
	~Animaciones();
	void Animacion_Ready(Bitmap^Img_Ready, BufferedGraphics^buffer, int timer_ticks)
	{
		switch (timer_ticks)
		{
		case 5: i_ready = 0; break;
		case 10: i_ready = 1; break;
		case 15: i_ready = 0; break;
		case 20: i_ready = 1; break;
		case 25: i_ready = 0; break;
		case 30: i_ready = 1; break;
		}
		Rectangle Origen = Rectangle(0, 113 * i_ready, 600, 100);
		Rectangle Pantalla = Rectangle(X_ready, 200, 480, 80);
		buffer->Graphics->DrawImage(Img_Ready, Pantalla, Origen, GraphicsUnit::Pixel);
		if (X_ready < 250)
		{
			X_ready += 150;
		}
	}

};



