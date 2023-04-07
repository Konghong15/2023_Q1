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
		load(eSpriteType::PLAYER_RUN, "run.txt");
		load(eSpriteType::PLAYER_ATTACK, "attack.txt");
		load(eSpriteType::PLAYER_JUMP, "jump.txt");
		load(eSpriteType::PROJECTIE, "projectile.txt");

		load(eSpriteType::MAP_1, "map_1.txt");

		load(eSpriteType::ENEMY_0, "enemy_0.txt");
		load(eSpriteType::ENEMY_1, "enemy_1.txt");
		load(eSpriteType::ENEMY_1_PROJECTILE, "bat_projectile.txt");
		load(eSpriteType::ENEMY_2, "enemy_2.txt");
		load(eSpriteType::BOSS_0_IDLE, "Boss_0_idle.txt");
		load(eSpriteType::BOSS_0_JUMP, "Boss_0_jump.txt");
		load(eSpriteType::BOSS_1_IDLE, "Boss_1_idle.txt");
		load(eSpriteType::BOSS_1_ATTACK, "Boss_1_attack.txt");
		load(eSpriteType::BOSS_2_IDLE, "Boss_2_idle.txt");
		load(eSpriteType::BOSS_2_ATTACK, "Boss_2_attack.txt");
		load(eSpriteType::BOSS_2_PROJECTILE, "Boss_2_projectile.txt");
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

		printf("%s %d\n", fileName, sp->Height);
		char* img = new char[fileSize];
		fin.read(img, fileSize);

		sp->Img = img;
		mSpriteMap.insert({ spriteType, sp });

		fin.close();
	}
}