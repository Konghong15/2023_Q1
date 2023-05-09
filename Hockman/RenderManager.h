#pragma once

#include <Windows.h>

#include "eSpriteType.h"
#include "hRectangle.h"

namespace hockman
{
	class RenderManager
	{
	public:
		static RenderManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Render();
		void Release();

		void Draw(eSpriteType spritType, hRectangle worldRect, hRectangle uvRect, bool isRight = true);
		void DrawRect(int x, int y, int w, int h, COLORREF color);
		void DrawRect(hRectangle rectangle, COLORREF color);
		void DrawLine(int startX, int startY, int endX, int endY, COLORREF color);
		void DrawPoint(int x, int y, COLORREF color);

		inline HDC GetFrontDC() const;
		inline HDC GetBackDC() const;

	private:
		RenderManager() = default;
		~RenderManager() = default;

	private:
		static RenderManager* mInstance;

		HDC mFrontHDC;
		HDC mBackHDC;
		HBITMAP mBackBitMap;

		HDC mTempBackHDC;
		HBITMAP mTempBackBitMap;
	};

	HDC RenderManager::GetFrontDC() const
	{
		return mFrontHDC;
	}

	HDC RenderManager::GetBackDC() const
	{
		return mBackHDC;
	}
}