#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "WinApp.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

#pragma comment(lib, "msimg32.lib")

namespace catInWonderland
{
	RenderManager* RenderManager::mInstance = nullptr;

	RenderManager* RenderManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new RenderManager();
			mInstance->init();
		}

		return mInstance;
	}

	void RenderManager::DeleteInstance()
	{
		mInstance->release();
		delete mInstance;
		mInstance = nullptr;
	}

	void RenderManager::init()
	{
		mFrontHDC = GetDC(WinApp::GetHWND());
		mBackHDC = CreateCompatibleDC(mFrontHDC);
		mBackBitMap = CreateCompatibleBitmap(mFrontHDC, WinApp::GetWidth(), WinApp::GetHeight());
		SelectObject(mBackHDC, mBackBitMap);

		mTempBackHDC = CreateCompatibleDC(mFrontHDC);
		mTempBackBitMap = CreateCompatibleBitmap(mFrontHDC, WinApp::GetWidth(), WinApp::GetHeight());
		SelectObject(mTempBackHDC, mTempBackBitMap);
	}

	void RenderManager::release()
	{
		DeleteObject(mBackBitMap);
		DeleteObject(mTempBackBitMap);
		DeleteDC(mBackHDC);
		DeleteDC(mTempBackHDC);
		ReleaseDC(WinApp::GetHWND(), mFrontHDC);
	}

	void RenderManager::Render()
	{
		BitBlt(mFrontHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackHDC, 0, 0, SRCCOPY);
		PatBlt(mBackHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::Draw(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex)
	{
		const Sprite& sprite = SpriteManager::GetInstance()->GetSprite(spritType);

		const Vector2& topLeft = worldRect.GetTopLeft();
		const Vector2& topRight = worldRect.GetTopRight();
		const Vector2& bottomLeft = worldRect.GetBottomLeft();

		POINT points[3] = { 0, };

		points[0] = { static_cast<long>(topLeft.GetX()), static_cast<long>(topLeft.GetY()) };
		points[1] = { static_cast<long>(topRight.GetX()), static_cast<long>(topRight.GetY()) };
		points[2] = { static_cast<long>(bottomLeft.GetX()), static_cast<long>(bottomLeft.GetY()) };

		const size_t cx = 756;
		const size_t cy = 57;
		const size_t cw = 273;
		const size_t ch = 492;

		PlgBlt(mTempBackHDC, points, sprite.Hdc, cx, cy, cw, ch, 0, 0, 0);

		const hRectangle boundingRectangle = hRectangle::GetBoundingRectangle(worldRect);
		const Vector2& boundingTopLeft = boundingRectangle.GetTopLeft();
		const Vector2& boundingBottomRight = boundingRectangle.GetBottomRight();

		TransparentBlt(mBackHDC,
			static_cast<int>(boundingTopLeft.GetX()),
			static_cast<int>(boundingTopLeft.GetY()),
			static_cast<int>(boundingBottomRight.GetX() - boundingTopLeft.GetX()),
			static_cast<int>(boundingBottomRight.GetX() - boundingTopLeft.GetX()),
			mTempBackHDC,
			static_cast<int>(boundingTopLeft.GetX()),
			static_cast<int>(boundingTopLeft.GetY()),
			static_cast<int>(boundingBottomRight.GetY() - boundingTopLeft.GetY()),
			static_cast<int>(boundingBottomRight.GetY() - boundingTopLeft.GetY()),
			RGB(255, 255, 255)); // 0 255 255 

		PatBlt(mTempBackHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::DrawRect(hRectangle rectangle, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		HPEN hPrevPen = (HPEN)SelectObject(mBackHDC, hPen);

		const Vector2& topLeft = rectangle.GetTopLeft();
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

	void RenderManager::rotateRender(float radian)
	{
		POINT points[3] = { 0, };

		points[0] = { 0,0 };
		points[1] = { static_cast<LONG>(WinApp::GetWidth()), 0 };
		points[2] = { 0, static_cast<LONG>(WinApp::GetHeight()) };

		POINT center = { static_cast<LONG>(WinApp::GetWidth()) / 2 , static_cast<LONG>(WinApp::GetHeight()) / 2 };
		{
			for (int i = 0; i < 3; ++i)
			{
				points[i].x -= center.x;
				points[i].y -= center.y;
			}
		}

		// 회전
		{
			float cosScalr = cos(radian);
			float sinScalr = sin(radian);
			POINT temp;

			for (int i = 0; i < 3; ++i)
			{
				temp.x = points[i].x * cosScalr - points[i].y * sinScalr;
				temp.y = points[i].x * sinScalr + points[i].y * cosScalr;
				points[i] = temp;
			}
		}

		// 월드 좌표로 원점이동
		{
			for (int i = 0; i < 3; ++i)
			{
				points[i].x += center.x;
				points[i].y += center.y;
			}
		}

		PlgBlt(mFrontHDC, points, mBackHDC, 0, 0, static_cast<LONG>(WinApp::GetWidth()), static_cast<LONG>(WinApp::GetHeight()), 0, 0, 0);
	}
};