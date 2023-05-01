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
		load(eSpriteType::PLAYER_IDLE, "./resource/idle.txt");
		load(eSpriteType::PLAYER_RUN_0, "./resource/run_0.txt");
		load(eSpriteType::PLAYER_RUN_1, "./resource/run_1.txt");
		load(eSpriteType::PLAYER_ATTACK, "./resource/attack.txt");
		load(eSpriteType::PLAYER_JUMP, "./resource/jump.txt");
		load(eSpriteType::PLAYER_JUMP_DOWN, "./resource/jump_down.txt");

		load(eSpriteType::PLAYER_WOUNDED_0, "./resource/wounded_0.txt");
		load(eSpriteType::PLAYER_WOUNDED_1, "./resource/wounded_1.txt");

		load(eSpriteType::PLAYER_DEAD_0, "./resource/dead_ani_0.txt");
		load(eSpriteType::PLAYER_DEAD_1, "./resource/dead_ani_1.txt");
		load(eSpriteType::PLAYER_DEAD_2, "./resource/dead_ani_2.txt");
		load(eSpriteType::PLAYER_DEAD_3, "./resource/dead_ani_3.txt");

		load(eSpriteType::PROJECTIE, "./resource/projectile.txt");
		load(eSpriteType::PROJECTIE_EFFECT, "./resource/hit_effect.txt");

		load(eSpriteType::TITLE_BG_0, "./resource/map_1_0.txt");
		load(eSpriteType::TITLE_BG_1, "./resource/title.txt");
		load(eSpriteType::GAME_BG, "./resource/game_map.txt");

		load(eSpriteType::ENEMY_0, "./resource/enemy_0.txt");
		load(eSpriteType::ENEMY_1, "./resource/enemy_1.txt");
		load(eSpriteType::ENEMY_1_PROJECTILE, "./resource/bat_projectile.txt");
		load(eSpriteType::ENEMY_2, "./resource/enemy_2.txt");
		load(eSpriteType::BOSS_0_IDLE, "./resource/Boss_0_idle.txt");
		load(eSpriteType::BOSS_0_JUMP, "./resource/Boss_0_jump.txt");
		load(eSpriteType::BOSS_1_IDLE, "./resource/Boss_1_idle.txt");
		load(eSpriteType::BOSS_1_ATTACK, "./resource/Boss_1_attack.txt");
		load(eSpriteType::BOSS_2_IDLE, "./resource/Boss_2_idle.txt");
		load(eSpriteType::BOSS_2_ATTACK, "./resource/Boss_2_attack.txt");
		load(eSpriteType::BOSS_2_PROJECTILE, "./resource/Boss_2_projectile.txt");

		load(eSpriteType::MONSTER_DEAD, "./resource/monster_dead_effect.txt");
		load(eSpriteType::UI, "./resource/ui.txt");
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