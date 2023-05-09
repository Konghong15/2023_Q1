#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "WinApp.h"

#pragma comment(lib, "msimg32.lib")

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

		mTempBackHDC = CreateCompatibleDC(mFrontHDC);
		mTempBackBitMap = CreateCompatibleBitmap(mFrontHDC, WinApp::GetWidth(), WinApp::GetHeight());
		SelectObject(mTempBackHDC, mTempBackBitMap);
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

	void RenderManager::Draw(eSpriteType spritType, hRectangle worldRect, hRectangle uvRect, bool isRight)
	{
		const Sprite& sprite = SpriteManager::GetInstance()->GetSprite(spritType);

		const Vector2& pos = worldRect.GetPos();
		const Vector2& size = worldRect.GetSize();
		const Vector2& uvPos = uvRect.GetPos();
		const Vector2& uvSize = uvRect.GetSize();

		if (isRight)
		{
			TransparentBlt(mBackHDC,
				static_cast<int>(pos.GetX()),
				static_cast<int>(pos.GetY()),
				static_cast<int>(size.GetX()),
				static_cast<int>(size.GetY()),
				sprite.Hdc,
				static_cast<int>(uvPos.GetX()),
				static_cast<int>(uvPos.GetY()),
				static_cast<int>(uvSize.GetX()),
				static_cast<int>(uvSize.GetY()),
				RGB(210, 230, 210));
		}
		else
		{
			POINT points[3] = { 0, };

			points[0] = { static_cast<long>(pos.GetX()),  static_cast<long>(pos.GetY()) };
			points[1] = { static_cast<long>(pos.GetX() + size.GetY()),  static_cast<long>(pos.GetY()) };
			points[2] = { static_cast<long>(pos.GetX()),  static_cast<long>(pos.GetY() + size.GetY()) };

			PlgBlt(mTempBackHDC, points, sprite.Hdc,
				static_cast<int>(uvPos.GetX() + uvSize.GetX()),
				static_cast<int>(uvPos.GetY()),
				-static_cast<int>(uvSize.GetX()),
				static_cast<int>(uvSize.GetY()),
				0, 0, 0);

			TransparentBlt(mBackHDC,
				static_cast<int>(pos.GetX()),
				static_cast<int>(pos.GetY()),
				static_cast<int>(size.GetX()),
				static_cast<int>(size.GetY()),
				mTempBackHDC,
				static_cast<int>(pos.GetX()),
				static_cast<int>(pos.GetY()),
				static_cast<int>(size.GetX()),
				static_cast<int>(size.GetY()),
				RGB(210, 230, 210));
		}
	}

	void RenderManager::DrawRect(hRectangle rectangle, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		HPEN hPrevPen = (HPEN)SelectObject(mBackHDC, hPen);

		const Vector2& topLeft = rectangle.GetPos();
		const Vector2& bottomRight = rectangle.GetBottomRight();

		Rectangle(mBackHDC,
			static_cast<int>(topLeft.GetX()),
			static_cast<int>(topLeft.GetY()),
			static_cast<int>(bottomRight.GetX()),
			static_cast<int>(bottomRight.GetY()));

		SelectObject(mBackHDC, hPrevPen);
		DeleteObject(hPen);
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