#pragma once

#include <Windows.h>

#include "Scene.h"
#include "eSpriteType.h"

namespace hongpireSurvivors
{
	class Player;
	class Object;

	enum eGameEvent
	{
		ZOMBIES = 100,
		BATS = 400,
		DEVILS = 600,
		ORGES = 800,
		BOSS_1 = 1198,
		BOSS_2 = 1199,
	};

	class GameScene : public Scene
	{
	public:
		GameScene(eSpriteType background, COORD sceneSize, COORD camaraPos = { 0,0 });
		~GameScene() = default;

		virtual void Enter() override;
		virtual void Frame() override;
		virtual void Exit() override;

	private:
		void handleCamara();
		void handleEvent();
		void SpawnMonster(eGameEvent gameEvent);

	private:
		eSpriteType mBGSpriteType;
		eGameEvent mCurEvent;
		bool mIsCamaraMove;

	};
}