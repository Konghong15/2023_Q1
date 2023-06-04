#include <windows.h>

#include "Stage01.h"
#include "Player.h"
#include "BoardManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "WinApp.h"
#include "Map.h"
#include "Tile.h"
#include "Brick.h"
#include "Butterfly.h"
#include "TimeManager.h"
#include "SceneLoader.h"
#include "PlayerState.h"
#include "ConstantTable.h"
#include "GuideButton.h"
#include "SoundManager.h"
#include "PlummetObject.h"

namespace catInWonderland
{
	Stage01::Stage01(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE01, eSceneType::STAGE02, 3u, 0u, 1.f, eSpriteType::StageName1, eSpriteType::YellowTile, boardObjectInfos)
		, mActionButtonInterval(0.f)
		, mGuideButtonInterval(0.f)
		, mbPlayerActionCheck(false)
		, mbPlayerMoveCheck(false)
		, mDirectionGuideButton{ nullptr, }
	{
	}

	void Stage01::Enter()
	{
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage12BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage01), eLayerType::Background);
		RegisterObject(object);
		GameScene::Enter();

		mDirectionGuideButton[0] = new GuideButton(BUTTON_A_WORLD_RECT, BUTTON_A_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ButtonA), eLayerType::NonBlendObject, 0.7f);
		mDirectionGuideButton[1] = new GuideButton(BUTTON_D_WORLD_RECT, BUTTON_D_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ButtonD), eLayerType::NonBlendObject, 0.7f);
		mDirectionGuideButton[0]->Excute();
		mDirectionGuideButton[1]->Excute();
		mActionGuideButton = new GuideButton(BUTTON_W_WORLD_RECT, BUTTON_W_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ButtonW), eLayerType::NonBlendObject, 0.7f);
		RegisterObject(mDirectionGuideButton[0]);
		RegisterObject(mDirectionGuideButton[1]);
		RegisterObject(mActionGuideButton);

		CreateGuideButterfly(eAnimationType::RedButterfly, eSpriteType::Guide11, eSpriteType::Guide12);
		ExcuteButterfly(0);

		mbPlayerMoveCheck = false;
		mbPlayerActionCheck = false;
		mGuideButtonInterval = 0.f;
		mActionButtonInterval = 0.f;
	}

	void Stage01::Update()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mPlayer->GetStageClear())
		{
			mClearImage->Excute();
			mClearImage->Update();
			mClearInterval += DELTA_TIME;

			return;
		}

		if (InputManager::GetInstance()->GetKeyState('R') == eKeyState::PUSH)
		{
			Exit();
			Enter();
		}

		if (mPlayer->GetPlayerState() == ePlayerStateType::Move)
		{
			if (!mbPlayerMoveCheck)
			{
				TurnOffButterfly(0);
			}
			mbPlayerMoveCheck = true;
		}
		if (mPlayer->GetBoardX() == mBrick->GetBoardX() && mButterfly->GetIsRed() != mBrick->GetIsRed())
		{
			mbPlayerActionCheck = true;
			ExcuteButterfly(1);
		}
		else
		{
			mbPlayerActionCheck = false;
			if (mbPlayerMoveCheck)
			{
				TurnOffButterfly(1);
			}
		}

		mGuideButtonInterval += DELTA_TIME;
		if (mGuideButtonInterval >= 1.0f && !mbPlayerMoveCheck)
		{
			mGuideButtonInterval = 0.f;
			mDirectionGuideButton[0]->Excute();
			mDirectionGuideButton[1]->Excute();
		}

		mActionButtonInterval += DELTA_TIME;
		if (mActionButtonInterval >= 1.0f && mbPlayerActionCheck)
		{
			mActionButtonInterval = 0.f;
			mActionGuideButton->Excute();
		}

		Scene::Update();
	}

	void Stage01::Render()
	{
		if (mPlayer->GetStageClear())
		{
			mClearImage->Render();

			for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				if ((*iter) != mActionGuideButton)
				{
					(*iter)->Render();
				}
			}
		}
		else
		{
			Scene::Render();
		}
	}

	void Stage01::Exit()
	{
		GameScene::Exit();
		mDirectionGuideButton[0] = nullptr;
		mDirectionGuideButton[1] = nullptr;
		mActionGuideButton = nullptr;
	}
}