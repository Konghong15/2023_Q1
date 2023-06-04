#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "WinApp.h"
#include "Vector2.h"

#pragma comment(lib, "msimg32.lib")

namespace catInWonderland
{
	RenderManager::RenderManager()
		: mScales{ 0.f, }
		, mAlphas{ 0, }
	{
		mFrontMemDC = GetDC(WinApp::GetWindow());

		for (unsigned int i = 0; i < static_cast<unsigned int>(eLayerType::Size); ++i)
		{
			mScales[i] = 1.f;
			mAlphas[i] = 255;
			mLayerDCs[i] = CreateCompatibleDC(mFrontMemDC);
			mLayerBitmaps[i] = CreateCompatibleBitmap(mFrontMemDC, WinApp::GetWidth(), WinApp::GetHeight());
			SelectObject(mLayerDCs[i], mLayerBitmaps[i]);
		}

		//   mAlphas[static_cast<unsigned int>(eLayerType::PostProcessing)] = 0.f;

		mBackMemDC = CreateCompatibleDC(mFrontMemDC);
		mRotateMemDC = CreateCompatibleDC(mFrontMemDC);
		mScaleDC = CreateCompatibleDC(mFrontMemDC);
		mBlendDC = CreateCompatibleDC(mFrontMemDC);

		mBackBitmap = CreateCompatibleBitmap(mFrontMemDC, WinApp::GetWidth(), WinApp::GetHeight());
		mRotateBitmap = CreateCompatibleBitmap(mFrontMemDC, WinApp::GetWidth(), WinApp::GetHeight());
		mScaleBitmap = CreateCompatibleBitmap(mFrontMemDC, WinApp::GetWidth(), WinApp::GetHeight());
		mBlendBitmap = CreateCompatibleBitmap(mFrontMemDC, WinApp::GetWidth(), WinApp::GetHeight());

		SelectObject(mBackMemDC, mBackBitmap);
		SelectObject(mRotateMemDC, mRotateBitmap);
		SelectObject(mScaleDC, mScaleBitmap);
		SelectObject(mBlendDC, mBlendBitmap);
	}

	RenderManager::~RenderManager()
	{
		for (unsigned int i = 0; i < static_cast<unsigned int>(eLayerType::Size); ++i)
		{
			DeleteDC(mLayerDCs[i]);
			DeleteObject(mLayerBitmaps[i]);
		}

		DeleteObject(mBackBitmap);
		DeleteObject(mRotateBitmap);
		DeleteObject(mScaleBitmap);
		DeleteObject(mBlendBitmap);

		DeleteDC(mBackMemDC);
		DeleteDC(mRotateMemDC);
		DeleteDC(mScaleDC);
		DeleteDC(mBlendDC);

		ReleaseDC(WinApp::GetWindow(), mFrontMemDC);
	}

	void RenderManager::Render()
	{
		BitBlt(mBackMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mLayerDCs[static_cast<unsigned int>(eLayerType::Background)], 0, 0, SRCCOPY);
		PatBlt(mLayerDCs[static_cast<unsigned int>(eLayerType::Background)], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);

		for (unsigned int i = 1; i < static_cast<unsigned int>(eLayerType::PostProcessing); ++i)
		{
			unsigned int width = static_cast<unsigned int>(WinApp::GetWidth() * mScales[i]);
			unsigned int height = static_cast<unsigned int>(WinApp::GetHeight() * mScales[i]);
			int x = (static_cast<int>(WinApp::GetWidth()) - static_cast<int>(width)) / 2;
			int y = (static_cast<int>(WinApp::GetHeight()) - static_cast<int>(height)) / 2;

			BLENDFUNCTION bf = { 0, };
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = mAlphas[i];

			//StretchBlt(mScaleDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mLayerDCs[i], x, y, width, height, SRCCOPY);
			//BitBlt(mLayerDCs[i], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackMemDC, 0, 0, SRCCOPY);
			//BitBlt(mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackMemDC, 0, 0, SRCCOPY);
			//TransparentBlt(mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mScaleDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), RGB(255, 255, 255));
			//AlphaBlend(mLayerDCs[i], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), bf);
			//TransparentBlt(mBackMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mLayerDCs[i], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), RGB(255, 255, 255));

			BitBlt(mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackMemDC, 0, 0, SRCCOPY);
			TransparentBlt(mBlendDC, x, y, width, height, mLayerDCs[i], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), RGB(255, 255, 255));
			AlphaBlend(mBackMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), bf);
			//PatBlt(mBlendDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
			PatBlt(mLayerDCs[i], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
		}
		{
			unsigned int index = static_cast<unsigned int>(eLayerType::PostProcessing);
			BLENDFUNCTION bf = { 0, };
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = mAlphas[index];
			AlphaBlend(mBackMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mLayerDCs[index], 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), bf);
		}

		BitBlt(mFrontMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), mBackMemDC, 0, 0, SRCCOPY);
		PatBlt(mBackMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::Draw(const hRectangle& worldRectangle, const hRectangle& spriteRectangle, const Sprite& sprite, eLayerType layerType, bool bLeft)
	{
		const Vector2& topLeft = worldRectangle.GetTopLeft();
		const Vector2& topRight = worldRectangle.GetTopRight();
		const Vector2& bottomLeft = worldRectangle.GetBottomLeft();
		const Vector2& bottomRight = worldRectangle.GetBottomRight();

		POINT points[3] = { 0, };

		if (bLeft)
		{
			points[0] = { static_cast<long>(topLeft.GetX()), static_cast<long>(topLeft.GetY()) };
			points[1] = { static_cast<long>(topRight.GetX()), static_cast<long>(topRight.GetY()) };
			points[2] = { static_cast<long>(bottomLeft.GetX()), static_cast<long>(bottomLeft.GetY()) };
		}
		else
		{
			points[0] = { static_cast<long>(topRight.GetX()), static_cast<long>(topRight.GetY()) };
			points[1] = { static_cast<long>(topLeft.GetX()), static_cast<long>(topLeft.GetY()) };
			points[2] = { static_cast<long>(bottomRight.GetX()), static_cast<long>(bottomRight.GetY()) };
		}

		const Vector2& spritePosition = spriteRectangle.GetTopLeft();
		const Vector2& spriteSize = spriteRectangle.GetSize();

		PlgBlt(mRotateMemDC, points, sprite.Hdc, static_cast<int>(spritePosition.GetX()), static_cast<int>(spritePosition.GetY()), static_cast<int>(spriteSize.GetX()), static_cast<int>(spriteSize.GetY()), 0, 0, 0);

		const hRectangle boundingRectangle = hRectangle::GetBoundingRectangle(worldRectangle);
		const Vector2& boundingTopLeft = boundingRectangle.GetTopLeft();
		const Vector2& boundingBottomRight = boundingRectangle.GetBottomRight();

		TransparentBlt(mLayerDCs[static_cast<unsigned int>(layerType)],
			static_cast<int>(boundingTopLeft.GetX()),
			static_cast<int>(boundingTopLeft.GetY()),
			static_cast<int>(boundingBottomRight.GetX() - boundingTopLeft.GetX()),
			static_cast<int>(boundingBottomRight.GetY() - boundingTopLeft.GetY()),
			mRotateMemDC,
			static_cast<int>(boundingTopLeft.GetX()),
			static_cast<int>(boundingTopLeft.GetY()),
			static_cast<int>(boundingBottomRight.GetX() - boundingTopLeft.GetX()),
			static_cast<int>(boundingBottomRight.GetY() - boundingTopLeft.GetY()),
			RGB(255, 255, 255));

		PatBlt(mRotateMemDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight(), WHITENESS);
	}

	void RenderManager::SetPostProcessingColor(COLORREF color)
	{
		HDC currentDC = mLayerDCs[static_cast<unsigned int>(eLayerType::PostProcessing)];

		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(currentDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(currentDC, hBrush);

		Rectangle(currentDC, 0, 0, WinApp::GetWidth(), WinApp::GetHeight());
		RECT rect{ 0,0, static_cast<LONG>(WinApp::GetWidth()),static_cast<LONG>(WinApp::GetHeight()) };
		FillRect(currentDC, &rect, hBrush);

		SelectObject(currentDC, hOldPen);
		SelectObject(currentDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
}