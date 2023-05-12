#define _CRTDBG_MAP_ALLOC

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "WinApp.h"
#include "Test.h"
#include "PlayerState.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hockman::TestHelper();


	_CrtDumpMemoryLeaks();

	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	int result = hockman::WinApp::Run(hInstance, L"HockMan", 1920, 1080);
	hockman::PlayerState::Release();

	_CrtDumpMemoryLeaks();

	return result;
}