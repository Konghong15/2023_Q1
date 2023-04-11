#pragma once

#include "RenderManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Player.h"
#include "Helper.h"
#include "Zombie.h"
#include "Bat.h"
#include "Devil.h"
#include "Orge.h"
#include "FlyingOrge.h"
#include "KingOrge.h"
#include "Collider.h"
#include "Effect.h"
#include "ColliderManager.h"
#include "SoundManager.h"

namespace hongpireSurvivors
{
	Scene* Scene::mScene = nullptr;

	Scene::Scene(COORD mapSize, eSpriteType backgrounds[], size_t backgroundLength, COORD backGroundSize, COORD camaraPos)
		: mMapSize(mapSize)
		, mBackgroundSize(backGroundSize)
		, mCamara(camaraPos)
		, mBackgroundLength(backgroundLength)
		, mBackgrounds(new eSpriteType[mBackgroundLength])
		, mUI(nullptr)
	{
		for (int i = 0; i < backgroundLength; ++i)
		{
			mBackgrounds[i] = backgrounds[i];
		}

		eSpriteType spriteTypes[1] = { eSpriteType::UI };
		mUI = new Effect({ 100, 2 }, { 100, 30 }, spriteTypes, 1, 10, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::WHITE), false);
		SoundManager::GetInstance()->Play(eSound::BGM);
		Init();
	}

	Scene::~Scene()
	{
		delete[] mBackgrounds;
		delete mPlayer;
		delete mUI;
	}

	void Scene::Init()
	{
		memset(mIsEvents, 0, sizeof(bool) * 6);

		mPlayer = new Player({ 40, 52 }, { 15, 15 }, eSpriteType::PLAYER_IDLE);
		Collider* collider = new Collider({ 10, 10 }, { 2, 2 }, *mPlayer);
		mPlayer->AddCollider(collider);
		ColliderManager::GetInstance()->OnRegister(collider);
		mCamara.X = 0;
		mElapsed = 0.f;
		mSceneEndElapsed = 0.f;
	}

	void Scene::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		mUI->Render();

		if (mPlayer == nullptr)
		{
			Init();
			return;
		}

		if (ObjectManager::GetInstance()->GetObjectCount() == 0)
		{
			mCanCamaraMove = true;
		}

		if (mCanCamaraMove)
		{
			mCamara.X = Helper::Clamp(0, 1199, mPlayer->GetPos().X - 185);
		}

		handleMap();
		handleSceneState();
		handleSpawnMonster();
	}

	void Scene::handleSceneState()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mPlayer->GetValid())
		{
			mPlayer->Frame();
			mPlayer->Render();

			if (mIsEvents[5] && ObjectManager::GetInstance()->GetObjectCount() == 0)
			{
				eSpriteType spriteTypes[4] = { eSpriteType::PLAYER_DEAD_0, eSpriteType::PLAYER_DEAD_1, eSpriteType::PLAYER_DEAD_2, eSpriteType::PLAYER_DEAD_3 };
				Effect* effect = new Effect({ (SHORT)(mPlayer->GetPos().X), (SHORT)(67 - 17) }, { (SHORT)20, (SHORT)17 }, spriteTypes, 4, 0.5f, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE), mPlayer->GetIsLeft());
				ObjectManager::GetInstance()->OnSpawn(effect);
				mPlayer->mIsVaild = false;
			}
		}
		else
		{
			mSceneEndElapsed += DELTA_TIME;

			if (mSceneEndElapsed > 3.0f)
			{
				ObjectManager::DeleteInstance();
				ColliderManager::DeleteInstance();
				delete mPlayer;
				mPlayer = nullptr;
				Init();
			}
		}
	}

	void Scene::handleSpawnMonster()
	{
		if (mIsEvents[4] && !mIsEvents[5] && ObjectManager::GetInstance()->GetObjectCount() == 0)
		{
			Monster* monster = new KingOrge({ 1500, 67 - 33 }, { 35, 33 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 30, 33);
			monster = new KingOrge({ 1250, 67 - 33 }, { 35, 33 }, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 30, 33);

			mCamara.X = 1199;
			mIsEvents[5] = true;
			mCanCamaraMove = false;
		}
		else if (mCamara.X >= SPAWN_POINT_4 && !mIsEvents[4])
		{
			Monster* monster = new FlyingOrge({ 1550, 67 - 26 - 20 }, { 30, 26 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 30, 26);
			monster = new FlyingOrge({ 1220, 67 - 26 - 20 }, { 30, 26 }, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 30, 26);

			mIsEvents[4] = true;
			mCanCamaraMove = false;
		}
		else if (mCamara.X > SPAWN_POINT_3 && !mIsEvents[3])
		{
			Monster* monster = new Orge({ 1100, 67 - 29 }, { 30, 29 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 30, 29);
			monster = new Orge({ SPAWN_POINT_3, 67 - 29 }, { 30, 29 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 30, 29);
			/*monster = new Zombie({ mCamara.X, 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 15, 17);
			monster = new Zombie({ (SHORT)(mCamara.X + mBackgroundSize.X), 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 15, 17);*/

			mIsEvents[3] = true;
			mCanCamaraMove = false;
		}
		else if (mCamara.X > SPAWN_POINT_2 && !mIsEvents[2])
		{
			Monster* monster = new Devil({ (SHORT)(mCamara.X + mBackgroundSize.X - 21),10 }, { 20, 13 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 20, 13);
			monster = new Devil({ (SHORT)(mCamara.X), 5 }, { 20, 13 }, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 20, 13);
			//monster = new Devil({ (SHORT)(mCamara.X + mBackgroundSize.X - 21), 67 }, { 20, 13 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			//Helper::Spawn(monster, 20, 13);
			//monster = new Devil({ (SHORT)(mCamara.X), 67 }, { 20, 13 }, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			//Helper::Spawn(monster, 20, 13);

			mIsEvents[2] = true;
			mCanCamaraMove = false;
		}
		else if (mCamara.X > SPAWN_POINT_1 && !mIsEvents[1])
		{
			Monster* monster = new Bat({ mCamara.X, 67 - 20 - 15 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 20, 8);
			monster = new Bat({ (SHORT)(mCamara.X + 30), 67 - 20 - 10 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 20, 8);
			mIsEvents[1] = true;
			monster = new Bat({ mCamara.X, 67 - 20 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 20, 8);
			// monster = new Bat({ (SHORT)(mCamara.X + 50), 67 - 20 - 10 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			// Helper::Spawn(monster, 20, 8);

			monster = new Bat({ (SHORT)(mCamara.X + mBackgroundSize.X), 67 - 20 - 10 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 20, 8);
			// monster = new Bat({ (SHORT)(mCamara.X + mBackgroundSize.X - 30), 67 - 20 - 10 }, { 20, 8 }, eSpriteType::ENEMY_2, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			// Helper::Spawn(monster, 20, 8);

			mIsEvents[1] = true;
			mCanCamaraMove = false;
		}
		if (mCamara.X > SPAWN_POINT_0 && !mIsEvents[0])
		{
			Monster* monster = new Zombie({ (SHORT)(mCamara.X + 100), 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 20, 8);
			monster = new Orge({ mCamara.X, 67 - 29 }, { 30, 29 }, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 30, 29);
			monster = new Zombie({ (SHORT)(mCamara.X + 300), 67 - 17 }, { 15,17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 20, 8);
			monster = new Zombie({ mCamara.X, 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X, false);
			Helper::Spawn(monster, 15, 17);
			monster = new Zombie({ (SHORT)(mCamara.X + mBackgroundSize.X), 67 - 17 }, { 15, 17 }, eSpriteType::ENEMY_0, mCamara.X, mCamara.X + mBackgroundSize.X);
			Helper::Spawn(monster, 15, 17);

			mIsEvents[0] = true;
			mCanCamaraMove = false;
		}
	}

	void Scene::handleMap()
	{
		int index = mCamara.X / mBackgroundSize.X;
		int next = (index + 1) % mBackgroundLength;
		RenderManager::GetInstance()->DrawMap(mBackgrounds[index], mBackgrounds[next], mCamara.X % 400, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_GREEN));
	}
};