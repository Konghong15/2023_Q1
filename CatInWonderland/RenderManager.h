#pragma once

#include <Windows.h>

#include "eAnimationType.h"
#include "eSprtieType.h"
#include "hRectangle.h"

namespace catInWonderland
{
	class RenderManager
	{
	public:
		static RenderManager* GetInstance();
		static void DeleteInstance();

		void Render();

		void Draw(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex);
		void DrawReverseX(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex);
		void DrawReverseY(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex);
		void DrawRotate(hRectangle worldRect, eSpriteType spritType, eAnimationType animationType, int animationIndex);

		void DrawRect(int x, int y, int w, int h, COLORREF color);
		void DrawRect(hRectangle rectangle, COLORREF color);
		void DrawLine(int startX, int startY, int endX, int endY, COLORREF color);
		void DrawPoint(int x, int y, COLORREF color);

		inline HDC GetFrontDC() const;

	private:
		void rotateRender(float radian);

	private:
		RenderManager() = default;
		~RenderManager() = default;

		void init();
		void release();

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
}