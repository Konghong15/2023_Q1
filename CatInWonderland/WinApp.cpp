#include <Windows.h>

#include "WinApp.h"
#include "GameCore.h"

namespace catInWonderland
{
	HWND WinApp::mHWnd = NULL;
	UINT WinApp::mWidth = 0;
	UINT WinApp::mHeight = 0;

	int WinApp::Run(HINSTANCE hInstance, const WCHAR* name, UINT width, UINT height)
	{
		mWidth = width;
		mHeight = height;

		WNDCLASSEXW wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXW));

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = hInstance;
		wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
		wcex.lpszClassName = name;
		wcex.lpfnWndProc = WinApp::WndProc;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

		RegisterClassExW(&wcex);

		RECT rect = { 0, 0 ,width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
		UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

		mHWnd = CreateWindowW(
			name, name,
			WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
			(screenWidth - (rect.right - rect.left)) / 2,
			(screenHeight - (rect.bottom - rect.top)) / 2,
			width, height,
			nullptr, nullptr,
			hInstance, nullptr);

		ShowWindow(mHWnd, SW_SHOW);
		UpdateWindow(mHWnd);

		MSG msg = { 0, };
		GameCore::GetInstance()->Init();
		{
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					GameCore::GetInstance()->Frame();
				}
			}
		}
		GameCore::GetInstance()->Release();
		GameCore::DeletInstance();

		return (int)msg.wParam;
	}

	HWND WinApp::GetHWND()
	{
		return mHWnd;
	}

	UINT WinApp::GetWidth()
	{
		return mWidth;
	}

	UINT WinApp::GetHeight()
	{
		return mHeight;
	}

	LRESULT WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}
};