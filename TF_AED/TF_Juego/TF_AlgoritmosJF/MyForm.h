#pragma once
#include "Juego_go.h"

namespace TF_AlgoritmosJF {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			Juego_GO = new Juego_go();
			Img_Mapas = gcnew Bitmap("Img_Mapas.png");
			Img_Sonic = gcnew Bitmap("Img_Sonic.png");
			Img_Ready = gcnew Bitmap("Img_Ready.png");
			Img_menu1 = gcnew Bitmap("Img_menu1.png");
			Img_menu2 = gcnew Bitmap("Img_menu2.png");
			Img_fantasma = gcnew Bitmap("Img_fantasma.png");
			Img_moneda = gcnew Bitmap("Img_moneda.png");
			Img_portal = gcnew Bitmap("Img_portal.png");
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Juego_go* Juego_GO;

		Bitmap^ Img_portal;
		Bitmap^ Img_Mapas;
		Bitmap^ Img_Sonic;
		Bitmap^ Img_Ready;
		Bitmap^ Img_menu1;
		Bitmap^ Img_menu2;
		Bitmap^ Img_fantasma;
		Bitmap^Img_moneda;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
			 /// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 35;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1312, 604);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		Graphics^g = this->CreateGraphics();
		BufferedGraphicsContext^espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^buffer = espacio->Allocate(g, this->ClientRectangle);
		/*buffer->Graphics->Clear(Color::White);*/
		Img_Sonic->MakeTransparent(Img_Sonic->GetPixel(0, 0));
		Img_Ready->MakeTransparent(Img_Ready->GetPixel(0, 0));
		Img_menu2->MakeTransparent(Img_menu2->GetPixel(0, 0));
		Img_fantasma->MakeTransparent(Img_fantasma->GetPixel(0, 0));
		Img_moneda->MakeTransparent(Img_moneda->GetPixel(0, 0));
		Img_portal->MakeTransparent(Img_portal->GetPixel(0, 0));
	
		Juego_GO->EmpezarJuego(Img_menu1,Img_menu2,Img_Mapas, Img_Sonic,Img_fantasma, Img_moneda,Img_portal,Img_Ready, buffer, this->ClientRectangle.Width, this->ClientRectangle.Height);
		Juego_GO->CambiarMapa();
		if (Juego_GO->Get_GameOver() == true && Juego_GO->Get_Timerticks() > 40)
		{
			Juego_GO = new Juego_go();
		}
		buffer->Render(g);
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		
		Juego_GO->PresionaTecla(e->KeyCode);
	}
	private: System::Void MyForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		
		if (e->KeyData == Keys::Left || e->KeyData == Keys::Right)
		{
			Juego_GO->PresionaTecla(Keys::None);
		}
	}
	};
}
