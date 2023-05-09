#include <fstream>
#include <string>

#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"

namespace hockman
{
	SpriteManager* SpriteManager::mInstance = nullptr;

	SpriteManager* SpriteManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SpriteManager();
		}

		return mInstance;
	}

	void SpriteManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void SpriteManager::Init()
	{
		// load..
		load(eSpriteType::Player, "C:\\Users\\User\\Desktop\\rockman_resource\\img.bmp");
	}

	void SpriteManager::Release()
	{
		// delete all
		for (auto iter = mSpriteMap.begin(); iter != mSpriteMap.end(); ++iter)
		{
			delete iter->second;
		}
	}

	void SpriteManager::load(eSpriteType spriteType, const char* fileName)
	{
		Sprite* sprite = new Sprite;
		sprite->Hdc = CreateCompatibleDC(RenderManager::GetInstance()->GetFrontDC());
		sprite->Bitmap = (HBITMAP)LoadImageA(nullptr, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(sprite->Bitmap != nullptr);
		HBITMAP prevBitmap = (HBITMAP)SelectObject(sprite->Hdc, sprite->Bitmap);
		DeleteObject(prevBitmap);

		GetObject(sprite->Bitmap, sizeof(BITMAP), &sprite->BitInfo);

		mSpriteMap.emplace(spriteType, sprite);
	}
}