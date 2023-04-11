#pragma once

#include <Windows.h>

#include "eSpriteType.h"

namespace hongpireSurvivors
{
	class Player;
	class Object;

	class Scene
	{
	public:
		Scene(COORD sceneSize, eSpriteType backgrounds[], size_t backgroundLength, COORD backGroundSize, COORD camaraPos = { 0,0 });
		~Scene();

		void Init();
		void Frame();

		inline const Object& GetPlayer() const;
		inline const COORD& GetMapSize() const;
		inline const COORD& GetCamara() const;

	private:
		void handleSpawnMonster();
		void handleMap();
		void handleSceneState();

	public:
		static Scene* mScene;

	private:
		enum { SPAWN_POINT_0 = 100 };
		enum { SPAWN_POINT_1 = 300 };
		enum { SPAWN_POINT_2 = 500 };
		enum { SPAWN_POINT_3 = 800 };
		enum { SPAWN_POINT_4 = 1199 };

		Object* mUI;
		Player* mPlayer;

		COORD mMapSize;
		COORD mCamara;
		eSpriteType* mBackgrounds;
		size_t mBackgroundLength;
		COORD mBackgroundSize;

		float mElapsed;
		float mSceneEndElapsed;
		bool mIsEvents[6];
		bool mCanCamaraMove;
	};

	const Object& Scene::GetPlayer() const
	{
		return *((const Object*)mPlayer);
	}

	const COORD& Scene::GetMapSize() const
	{
		return mMapSize;
	}

	const COORD& Scene::GetCamara() const
	{
		return mCamara;
	}
}