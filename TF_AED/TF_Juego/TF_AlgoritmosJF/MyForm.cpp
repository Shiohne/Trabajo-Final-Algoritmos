#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(cli::array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew TF_AlgoritmosJF::MyForm());
}