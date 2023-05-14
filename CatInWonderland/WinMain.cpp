#define _CRTDBG_MAP_ALLOC

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "WinApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	const int WIDTH = 1600;
	const int HEIGHT = 1024;
	int result = catInWonderland::WinApp::Run(hInstance, L"catInWonderland", WIDTH, HEIGHT);

	return result;
}