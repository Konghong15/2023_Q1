#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace hockman
{
	class WinApp
	{
	public:
		WinApp() = delete;
		~WinApp() = delete;
		WinApp(const WinApp&) = delete;
		WinApp& operator=(const WinApp&) = delete;

		static int Run()
		static HWND GetWindow();
		
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		static HWND m_hWnd;
	};
}