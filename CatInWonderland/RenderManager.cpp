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
		static float degreeinRadian = 0.f;
		static float arrival = 0.f;

		static bool bEnd = false;
		static bool bSuccess = false;
		static bool bLeft = false;
		static float weight = 3.14159f / 1.f;

		if (InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
		{
			bLeft = false;
			arrival = 1.5708f;
		}
		else if (InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH)
		{
			bLeft = true;
			arrival = -1.5708f;
		}

		if (!bLeft)
		{
			if (degreeinRadian < arrival)
			{
				degreeinRadian += weight * TimeManager::GetInstance()->GetDeltaTime();
			}
			else
			{
				degreeinRadian = 0.f;
				arrival = 0.f;
			}
		}
		else
		{
			if (degreeinRadian > arrival)
			{
				degreeinRadian -= weight * TimeManager::GetInstance()->GetDeltaTime();
			}
			else
			{
				degreeinRadian = 0.f;
				arrival = 0.f;
			}
		}
		rotateRender(degreeinRadian);

		// BitBlt(mFrontHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackHDC, 0, 0, SRCCOPY);
		PatBlt(mBackHDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::Draw(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex)
	{
		/*const Sprite& sprite = SpriteManager::GetInstance()->GetSprite(spritType);

		const Vector2& pos = worldRect.GetTopLeft();
		const Vector2& size = worldRect.GetSize();
		const Vector2& uvPos = uvRect.GetTopLeft();
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
		}*/
	}

	void RenderManager::DrawReverseX(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex)
	{

	}
	void RenderManager::DrawReverseY(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex)
	{

	}

	void RenderManager::DrawRotate(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex)
	{

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