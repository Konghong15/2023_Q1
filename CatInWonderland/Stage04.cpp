#include <windows.h>

#include "Stage04.h"
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
	Stage04::Stage04(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE04, eSceneType::CutScene02, 8u, 3u, 1.f, eSpriteType::StageName4, eSpriteType::PurpleTile, boardObjectInfos)
	{
	}

	void Stage04::Enter()
	{
		// (°æ°í) UINT -> float
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage345BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage04), eLayerType::Background);
		RegisterObject(object);
		CreateGuideButterfly(eAnimationType::RedButterfly, eSpriteType::Guide41, eSpriteType::Guide41);
		ExcuteButterfly(0);
		GameScene::Enter();
	}

	void Stage04::Update()
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