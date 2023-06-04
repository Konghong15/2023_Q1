#pragma once

#include <Windows.h>

#include "eLayerType.h"

namespace catInWonderland
{
	class hRectangle;
	struct Sprite;

	class RenderManager final
	{
	public:
		RenderManager();
		~RenderManager();
		RenderManager(const RenderManager&) = delete;
		RenderManager operator=(const RenderManager&) = delete;

		void Render();

		void Draw(const hRectangle& worldRectangle, const hRectangle& spriteRectangle, const Sprite& sprite, eLayerType layerType = eLayerType::NonBlendObject, bool bLeft = true);

		void SetPostProcessingColor(COLORREF color);
		inline void SetScale(eLayerType layerType, float scale);
		inline void SetAlpha(eLayerType layerType, unsigned int alpha);

		inline HDC GetFrontDC() const;

	private:
		float mScales[static_cast<unsigned int>(eLayerType::Size)];
		unsigned int mAlphas[static_cast<unsigned int>(eLayerType::Size)];
		HDC mLayerDCs[static_cast<unsigned int>(eLayerType::Size)]; // FrameDC

		HBITMAP mLayerBitmaps[static_cast<unsigned int>(eLayerType::Size)];

		HDC mFrontMemDC;
		HDC mBackMemDC;
		HDC mRotateMemDC;
		HDC mScaleDC;
		HDC mBlendDC;

		HBITMAP mBackBitmap;
		HBITMAP mRotateBitmap;
		HBITMAP mScaleBitmap;
		HBITMAP mBlendBitmap;
	};

	void RenderManager::SetScale(eLayerType layerType, float scale)
	{
		mScales[static_cast<unsigned int>(layerType)] = scale;
	}

	void RenderManager::SetAlpha(eLayerType layerTpye, unsigned int alpha)
	{
		mAlphas[static_cast<unsigned int>(layerTpye)] = alpha;
	}

	HDC RenderManager::GetFrontDC() const
	{
		return mFrontMemDC;
	}

}