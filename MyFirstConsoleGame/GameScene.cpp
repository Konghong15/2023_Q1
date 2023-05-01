#include <cassert>

#include "GameScene.h"
#include "ObjectManager.h"
#include "Player.h"
#include "ColliderManager.h"
#include "Collider.h"
#include "RenderManager.h"
#include "Helper.h"

#include "Zombie.h"
#include "Bat.h"
#include "Devil.h"
#include "Orge.h"
#include "FlyingOrge.h"
#include "KingOrge.h"

namespace hongpireSurvivors
{
	GameScene::GameScene(eSpriteType background, COORD sceneSize, COORD camaraPos)
		: Scene(sceneSize, camaraPos)
		, mBGSpriteType(background)
		, mCurEvent(eGameEvent::ZOMBIES)
		, mIsCamaraMove(true)
	{
	}

	void GameScene::Enter()
	{
		Player* player = new Player({ 40, 52 }, { 15, 15 }, eSpriteType::PLAYER_IDLE);
		Collider* collider = new Collider({ 10, 10 }, { 2, 2 }, *player);
		player->AddCollider(collider);
		ColliderManager::GetInstance()->OnRegister(collider);

		ObjectManager::GetInstance()->RegisterPlayer(player);
		ObjectManager::GetInstance()->OnSpawn(player);
	}

	void GameScene::Frame()
	{
		RenderManager::GetInstance()->DrawMap(eSpriteType::GAME_BG, { 1599, 78 }, mCamaraPos, RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE));

		handleCamara();
		handleEvent();
	}

	void GameScene::Exit()
	{

	}


	void GameScene::handleCamara()
	{
		if (!mIsCamaraMove)
		{
			return;
		}

		COORD pos = ObjectManager::GetInstance()->GetPlayerOrNull()->GetPos();
		mCamaraPos.X = pos.X - 200;

		mCamaraPos.X = Helper::Clamp(0, mSceneSize.X - 400, mCamaraPos.X);
	}

	void GameScene::handleEvent()
	{
		if (!mIsCamaraMove && ObjectManager::GetInstance()->GetObjectCount() == 1)
		{
			mIsCamaraMove = true;
		}

		if (mCamaraPos.X >= static_cast<int>(mCurEvent))
		{
			mIsCamaraMove = false;
			SpawnMonster(mCurEvent);

			switch (mCurEvent)
			{
			case eGameEvent::ZOMBIES:
				mCurEvent = eGameEvent::BATS;
				break;
			case eGameEvent::BATS:
				mCurEvent = eGameEvent::DEVILS;
				break;
			case eGameEvent::DEVILS:
				mCurEvent = eGameEvent::ORGES;
				break;
			case eGameEvent::ORGES:
				mCurEvent = eGameEvent::BOSS_1;
				break;
			case eGameEvent::BOSS_1:
				mCurEvent = eGameEvent::BOSS_2;
				break;
			case eGameEvent::BOSS_2:
				mCurEvent = eGameEvent::BOSS_2;
				break;
			default:
				break;
			}
		}
	}

	void GameScene::SpawnMonster(eGameEvent gameEvent)
	{
		Monster* monster;
		COORD pos;
		COORD size;
		int min;
		int max;

		switch (mCurEvent)
		{
		case hongpireSurvivors::ZOMBIES:
			pos = { 100, 50 }; size = { 15, 17 }; min = 100; max = 500;
			monster = new Zombie(pos, size, eSpriteType::ENEMY_0, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { 150, 50 };
			monster = new Zombie(pos, size, eSpriteType::ENEMY_0, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { 250, 50 };
			monster = new Zombie(pos, size, eSpriteType::ENEMY_0, min, max, true);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { 300, 50 };
			monster = new Zombie(pos, size, eSpriteType::ENEMY_0, min, max, true);
			Helper::Spawn(monster, size.X, size.Y);
			break;
		case hongpireSurvivors::BATS:
			min = 300; max = 700;
			pos = { (SHORT)(min + 10), 32 }; size = { 20, 8 };
			monster = new Bat(pos, size, eSpriteType::ENEMY_2, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 50), 45 };
			monster = new Bat(pos, size, eSpriteType::ENEMY_2, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 100), 50 };
			monster = new Bat(pos, size, eSpriteType::ENEMY_2, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 350), 32 };
			monster = new Bat(pos, size, eSpriteType::ENEMY_2, min, max, true);
			Helper::Spawn(monster, size.X, size.Y);

			break;
		case hongpireSurvivors::DEVILS:
			min = 600; max = 1000;
			pos = { (SHORT)(min), 10 }; size = { 20, 13 };
			monster = new Devil(pos, size, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(max - size.X), 10 };
			monster = new Devil(pos, size, min, max, true);
			Helper::Spawn(monster, size.X, size.Y);
			break;
		case hongpireSurvivors::ORGES:
			min = 800; max = 1200;
			pos = { (SHORT)(min), 38 }; size = { 30, 29 };
			monster = new Orge(pos, size, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 300), 38 };
			monster = new Orge(pos, size, min, max, true);
			Helper::Spawn(monster, size.X, size.Y);
			break;
		case hongpireSurvivors::BOSS_1:
			min = 1200; max = 1599;
			pos = { (SHORT)(min + 20), 21 }; size = { 30, 26 };
			monster = new FlyingOrge(pos, size, min, max, false);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 320), 21 };
			monster = new FlyingOrge(pos, size, min, max);
			Helper::Spawn(monster, size.X, size.Y);
			break;
		case hongpireSurvivors::BOSS_2:
			min = 1200; max = 1599;
			pos = { (SHORT)(min + 50), 34 }; size = { 35, 33 };
			monster = new KingOrge(pos, size, min, max);
			Helper::Spawn(monster, size.X, size.Y);

			pos = { (SHORT)(min + 350), 34 };
			monster = new KingOrge(pos, size, min, max);
			Helper::Spawn(monster, size.X, size.Y);
			break;
		default:
			assert(false);
			break;
		}
	}
}