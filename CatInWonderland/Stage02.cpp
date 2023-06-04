#include <windows.h>

#include "Stage02.h"
#include "Map.h"
#include "WinApp.h"
#include "SpriteManager.h"
#include "BoardManager.h"
#include "Brick.h"
#include "Butterfly.h"
#include "Player.h"
#include "ConstantTable.h"
#include "SoundManager.h"
#include "GuideButton.h"
#include "TimeManager.h"
#include "InputManager.h"

namespace catInWonderland
{
	Stage02::Stage02(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE02, eSceneType::CutScene01, 3u, 1u, 1.f, eSpriteType::StageName2, eSpriteType::YellowTile, boardObjectInfos)
		, mGuideButton{ nullptr, }
		, mGuideButtonInterval(0.f)
		, mbPlayerMoveCheck(false)
	{
	}

	void Stage02::Enter()
	{
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage12BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage02), eLayerType::Background);
		RegisterObject(object);
		GameScene::Enter();

		mGuideButton[0] = new GuideButton(BUTTON_Q_WORLD_RECT, BUTTON_Q_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ButtonQ), eLayerType::Background, 0.7f);
		mGuideButton[1] = new GuideButton(BUTTON_E_WORLD_RECT, BUTTON_E_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ButtonE), eLayerType::Background, 0.7f);
		mGuideButton[0]->Excute();
		mGuideButton[1]->Excute();
		RegisterObject(mGuideButton[0]);
		RegisterObject(mGuideButton[1]);
		CreateGuideButterfly(eAnimationType::RedButterfly, eSpriteType::Guide21, eSpriteType::Guide21);
		ExcuteButterfly(0);

		mbPlayerMoveCheck = false;
		mGuideButtonInterval = 0.f;
	}

	void Stage02::Update()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mPlayer->GetPlayerState() == ePlayerStateType::Move
			|| InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH
			|| InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
		{
			mbPlayerMoveCheck = true;
			TurnOffButterfly(0);
		}

		mGuideButtonInterval += DELTA_TIME;
		if (mGuideButtonInterval >= 1.0f && !mbPlayerMoveCheck)
		{
			mGuideButtonInterval = 0.f;
			mGuideButton[0]->Excute();
			mGuideButton[1]->Excute();
		}

		GameScene::Update();
	}

	void Stage02::Exit()
	{
		GameScene::Exit();
		mGuideButton[0] = nullptr;
		mGuideButton[1] = nullptr;
	}
}