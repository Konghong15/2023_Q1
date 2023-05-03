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
		HPEN hOldPen = (HPEN)SelectObject(mBackHDC, hPen);

		Rectangle(mBackHDC, x, y, x + w, y + h);

		SelectObject(mBackHDC, hOldPen);
		DeleteObject(hPen);
	}
};