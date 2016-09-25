#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	P3DArduinoProgram::MainForm mainform;
	Application::Run(%mainform);
}

