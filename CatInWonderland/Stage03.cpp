#include <windows.h>

#include "Stage03.h"
#include "Map.h"
#include "WinApp.h"
#include "SpriteManager.h"
#include "BoardManager.h"
#include "Brick.h"
#include "Butterfly.h"
#include "Player.h"
#include "ConstantTable.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "InputManager.h"

namespace catInWonderland
{
	Stage03::Stage03(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE03, eSceneType::STAGE04, 7u, 3u, 1.f, eSpriteType::StageName3, eSpriteType::PurpleTile, boardObjectInfos)
	{
	}

	void Stage03::Enter()
	{
		// (°æ°í) UINT -> float
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage345BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage03), eLayerType::Background);
		RegisterObject(object);
		CreateGuideButterfly(eAnimationType::RedButterfly, eSpriteType::Guide31, eSpriteType::Guide31);
		ExcuteButterfly(0);

		GameScene::Enter();
	}

	void Stage03::Update()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mPlayer->GetPlayerState() == ePlayerStateType::Move
			|| InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH
			|| InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
		{
			TurnOffButterfly(0);
		}

		GameScene::Update();
	}

}