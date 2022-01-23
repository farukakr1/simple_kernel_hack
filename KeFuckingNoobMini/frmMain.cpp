#include <Windows.h>
#include "frmMain.h"

using namespace System;
using namespace System::Windows::Forms;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	KeFuckingNoobMini::frmMain form;
	Application::Run(% form);
	return 0;
}