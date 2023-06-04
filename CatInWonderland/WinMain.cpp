#define WIN32_LEAN_AND_MEAN

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <Windows.h>
#include "WinApp.h"

#ifndef NDEBUG
#include "UnitTest.h"
#endif /* NDEBUG */

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// SceneLoader에서 static map으로 인해 72byte, 16byte 메모리 누수가 있다 관찰됨
	// 수정 없이도 프로그램 종료 시 메모리가 해제되나 개선 방법이 있는지 체크할 필요가 있음
	_CrtDumpMemoryLeaks();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifndef NDEBUG
	catInWonderland::UnitTest::Test();
#endif /* NDEBUG */

	int result = catInWonderland::WinApp::Run(hInstance, TEXT("CatInWonderland"), 1920, 1080);

	_CrtDumpMemoryLeaks();

	return 0;
}