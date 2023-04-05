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
		load(eSpriteType::MONSTER_LEFT, "monster_left.txt");
		load(eSpriteType::PROJECTILE_RIGHT, "projectile_right.txt");
		load(eSpriteType::MAP_1, "map_1.txt");
	}

	void SpriteManager::load(eSpriteType spriteType, const char* fileName)
	{
		std::fstream fin;
		fin.open(fileName, std::ios_base::in | std::ios_base::binary);

		Sprite* sp = new Sprite();

		fin.seekg(0, std::ios_base::end);
		int fileSize = fin.tellg();
		fin.seekg(0, std::ios_base::beg);

		std::string garbage;
		fin >> sp->Width;
		getline(fin, garbage);

		int curPoint = fin.tellg();
		fileSize -= curPoint;

		sp->Height = fileSize / sp->Width;
		char* img = new char[fileSize];
		fin.read(img, fileSize);

		sp->Img = img;
		mSpriteMap.insert({ spriteType, sp });

		fin.close();
	}
}