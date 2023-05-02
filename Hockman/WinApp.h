#pragma once

namespace hockman
{
	class WinApp
	{
	public:
		WinApp() = delete;
		~WinApp() = delete;
		WinApp(const WinApp&) = delete;
		WinApp& operator=(const WinApp&) = delete;

		static int Run(HINSTANCE hInstance, const WCHAR* name, UINT width, UINT height);
		static HWND GetHWND();
		static UINT GetWidth();
		static UINT GetHeight();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		static HWND mHWnd;
		static UINT mWidth;
		static UINT mHeight;
	};
}