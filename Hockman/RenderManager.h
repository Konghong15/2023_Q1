#pragma once

#include <Windows.h>
#include "eSpriteType.h"

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

		void Draw(eSpriteType spritType, int x, int y);
		void DrawRect(int x, int y, int w, int h, COLORREF color);

	private:
		RenderManager() = default;
		~RenderManager() = default;

	private:
		static RenderManager* mInstance;

		HDC mFrontHDC;
		HDC mBackHDC;
		HBITMAP mBackBitMap;
	};
}