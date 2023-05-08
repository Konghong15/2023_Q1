#include "RenderManager.h"
#include "WinApp.h"

namespace hockman
{
	RenderManager* RenderManager::mInstance = nullptr;

	RenderManager* RenderManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new RenderManager();
		}

		return mInstance;
	}

	void RenderManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void RenderManager::Init()
	{
		mFrontHDC = GetDC(WinApp::GetHWND());
		mBackHDC = CreateCompatibleDC(mFrontHDC);
		mBackBitMap = CreateCompatibleBitmap(mFrontHDC, WinApp::GetWidth(), WinApp::GetHeight());
		SelectObject(mBackHDC, mBackBitMap);
	}

	void RenderManager::Render()
	{
		BitBlt(mFrontHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackHDC, 0, 0, SRCCOPY);
		PatBlt(mBackHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::Release()
	{
		DeleteObject(mBackBitMap);
		DeleteDC(mBackHDC);
		ReleaseDC(WinApp::GetHWND(), mFrontHDC);
	}

	void RenderManager::Draw(eSpriteType spritType, int x, int y)
	{

	}

	void RenderManager::DrawRect(int x, int y, int w, int h, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		HPEN hPrevPen = (HPEN)SelectObject(mBackHDC, hPen);

		Rectangle(mBackHDC, x, y, x + w, y + h);

		SelectObject(mBackHDC, hPrevPen);
		DeleteObject(hPen);
	}

	void RenderManager::DrawLine(int startX, int startY, int endX, int endY, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		HPEN hPrevPen = (HPEN)SelectObject(mBackHDC, hPen);

		MoveToEx(mBackHDC, startX, startY, NULL);
		LineTo(mBackHDC, endX, endY);

		SelectObject(mBackHDC, hPrevPen);
		DeleteObject(hPen);
	}

	void RenderManager::DrawPoint(int x, int y, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		HPEN hPrevPen = (HPEN)SelectObject(mBackHDC, hPen);

		for (int i = 0; i < 50; ++i)
		{
			for (int j = 0; j < 50; ++j)
			{
				SetPixel(mBackHDC, x + i, y + j, color);
			}
		}

		SelectObject(mBackHDC, hPrevPen);
		DeleteObject(hPen);
	}
};