#include <fstream>
#include <string>

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
	}

	void SpriteManager::Release()
	{
		// delete all
	}

	void SpriteManager::load(eSpriteType spriteType, const char* fileName)
	{
	}
}