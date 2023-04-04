#include <fstream>
#include <string>

#include "SpriteManager.h"

namespace hongpireSurvivors
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

	SpriteManager::SpriteManager()
	{
		load(eSpriteType::PLAYER_IDLE, "idle.txt");
	}

	void SpriteManager::load(eSpriteType spriteType, const char* fileName)
	{
		std::fstream fin;
		fin.open(fileName, std::ios_base::in | std::ios_base::binary);

		Sprite* sp = new Sprite();

		fin >> sp->Height;
		fin >> sp->Width;
		fin.get();

		char* img = new char[sp->Height * sp->Width];
		fin.read(img, sp->Height * sp->Width);

		sp->Img = img;
		mSpriteMap.insert({ spriteType, sp });

		fin.close();
	}
}