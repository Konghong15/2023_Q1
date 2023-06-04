#include <windows.h>

#include "GameScene.h"
#include "Player.h"
#include "BoardManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "WinApp.h"
#include "Tile.h"
#include "TimeManager.h"
#include "SceneLoader.h"
#include "Creator.h"
#include "Butterfly.h"
#include "Brick.h"
#include "ConstantTable.h"
#include "Button.h"
#include "ChangeColorTile.h"
#include "SoundManager.h"
#include "Map.h"
#include "PlummetObject.h"
#include "GuideButton.h"

namespace catInWonderland
{
	eSpriteType GameScene::mNumbers[MAX_NUMBER_COUNT] = {
		eSpriteType::RotateCountNumber0,
		eSpriteType::RotateCountNumber1,
		eSpriteType::RotateCountNumber2,
		eSpriteType::RotateCountNumber3,
		eSpriteType::RotateCountNumber4,
		eSpriteType::RotateCountNumber5,
		eSpriteType::RotateCountNumber6,
		eSpriteType::RotateCountNumber7
	};

	GameScene::GameScene(eSceneType sceneType, eSceneType nextScene, unsigned int boardSize, unsigned int limitRotateCount, float scale, eSpriteType stageTitleName, eSpriteType tileType, const std::vector<BoardObjectInfo>& boardObjectInfos)
		: Scene(sceneType)
		, mPlayer(nullptr)
		, mBrick(nullptr)
		, mButterfly(nullptr)
		, mBoardSize(boardSize)
		, mRotateSceneElapsed(0.f)
		, mRotateObjectElapsed(0.f)
		, mbRotateLeft(false)
		, mbRotateScene(false)
		, mbRotateObject(false)
		, mReturnButton(nullptr)
		, mNextScene(nextScene)
		, mEndClearInterval(2.f)
		, mClearInterval(0.f)
		, mLimitRotateCount(limitRotateCount)
		, mRotateCount(0u)
		, mScale(scale)
		, mStageTitleName(stageTitleName)
		, mClearImage(nullptr)
		, mRotateCountImage(nullptr)
		, mStageTitle()
		, mRotateImage()
		, mTileType(tileType)
		, mPlayerIdleElapsed(0.f)
		, mGuideButterflyOrNull(nullptr)
		, mGuideSpeechOrNull{ nullptr, }
		, mBoardObjectInfos(boardObjectInfos)
	{
	}

	void GameScene::CreateBoardObject()
	{
		auto iter = mBoardObjectInfos.begin();

		mPlayer = static_cast<Player*>(Creator::CreateBoardObject(*iter++));
		mBrick = static_cast<Brick*>(Creator::CreateBoardObject(*iter++));

		for (; iter != infos.end(); ++iter)
		{
			RegisterBoardObject(Creator::CreateBoardObject(*iter));
		}

		mButterfly = new Butterfly(hRectangle(mPlayer->GetWorldRectangle().GetTopLeft(), mPlayer->GetWorldRectangle().GetCenter()), BUTTER_FLY_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Butterfly), eObjectType::Butterfly, mPlayer, eLayerType::NonBlendObject, 0.f, true, mPlayer->GetIsLeft(), SpriteManager::GetInstance()->GetAnimator(eAnimationType::RedButterfly));
		RegisterBoardObject(mBrick);
		RegisterBoardObject(mPlayer);
		RegisterObject(mButterfly);
	}

	void GameScene::CreateTileObject()
	{
		BoardManager::GetInstance()->CreateBoard(mBoardSize, 170, 0);

		BoardObject* boardObject;
		for (unsigned int i = 0; i < mBoardSize; ++i)
		{
			for (unsigned int j = 0; j < mBoardSize; ++j)
			{
				boardObject = new Tile(BoardManager::GetInstance()->GetWorldRectangle(i, j),
					TILE_RECT,
					&SpriteManager::GetInstance()->GetSprite(mTileType),
					eLayerType::BlendObject,
					i, j);

				RegisterBoardObject(boardObject);
			}
		}
	}

	void GameScene::CreateGuideButterfly(eAnimationType butterflyType, eSpriteType firstSpeechBubble, eSpriteType secondSpeechBubble)
	{
		mGuideButterflyOrNull = new GuideButton(GUIDE_BUTTERFLY_RECT, SpriteManager::GetInstance()->GetSpriteRectangle(butterflyType, 0), &SpriteManager::GetInstance()->GetSprite(eSpriteType::Butterfly), eLayerType::Background, 120.f);
		mGuideButterflyOrNull->SetIsLeft(false);
		RegisterObject(mGuideButterflyOrNull);
		mGuideSpeechOrNull[0] = new GuideButton(hRectangle(115, 477, 534, 746), hRectangle(0, 0, 420, 270), &SpriteManager::GetInstance()->GetSprite(firstSpeechBubble), eLayerType::Background, 120.f);
		mGuideSpeechOrNull[1] = new GuideButton(hRectangle(115, 477, 534, 746), hRectangle(0, 0, 420, 270), &SpriteManager::GetInstance()->GetSprite(secondSpeechBubble), eLayerType::Background, 120.f);

		RegisterObject(mGuideSpeechOrNull[0]);
		RegisterObject(mGuideSpeechOrNull[1]);
	}

	void GameScene::ExcuteButterfly(unsigned int index)
	{
		assert(mGuideButterflyOrNull != nullptr);
		mGuideButterflyOrNull->Excute();
		assert(mGuideSpeechOrNull != nullptr);
		mGuideSpeechOrNull[index]->Excute();
	}

	void GameScene::TurnOffButterfly(unsigned int index)
	{
		assert(mGuideButterflyOrNull != nullptr);
		mGuideButterflyOrNull->TurnOff();
		assert(mGuideSpeechOrNull != nullptr);
		mGuideSpeechOrNull[index]->TurnOff();
	}

	void GameScene::Enter()
	{
		Scene::Enter();
		mRotateSceneElapsed = 0.f;
		mRotateObjectElapsed = 0.f;
		mbRotateLeft = true;
		mbRotateScene = false;
		mbRotateObject = false;
		mClearInterval = 0.f;
		mRotateCount = 0u;
		mPlayerIdleElapsed = 0.f;

		mReturnButton = new Button(hRectangle(1738, 19, 1907, 172), SET_BUTTON_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Home), eLayerType::Background);
		RegisterObject(mReturnButton);

		// Load tile Object;
		CreateTileObject();

		// Load Scene Data
		CreateBoardObject();

		// UI Object
		{
			mClearImage = new PlummetObject(CLEAR_WORLD_RECT, CLEAR_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::StageClear), eLayerType::NonBlendObject, CLEAR_PLUMMET_TIME, CLEAR_PLUMMET_DISTANCE);
			mStageTitle = new PlummetObject(STAGE_TITLE_WORLD_RECT, STAGE_TITLE_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(mStageTitleName), eLayerType::Background, STAGE_TITLE_PLUMMET_TIME, STAGE_TITLE_PLUMMET_DISTANCE);
			mRotateImage = new PlummetObject(ROTATE_COUNT_WORLD_RECT, ROTATE_COUNT_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::RotateCount), eLayerType::Background, ROTATE_COUNT_PLUMMET_TIME, ROTATE_COUNT_PLUMMET_DISTANCE);
			mRotateCountImage = new PlummetObject(ROTATE_COUNT_NUMBER_WORLD_RECT, ROTATE_COUNT_NUMBER_SPRITE_RECT, &SpriteManager::GetInstance()->GetSprite(mNumbers[mLimitRotateCount - mRotateCount]), eLayerType::Background, ROTATE_COUNT_PLUMMET_TIME, ROTATE_COUNT_PLUMMET_DISTANCE);
			RegisterObject(mClearImage);
			RegisterObject(mStageTitle);
			RegisterObject(mRotateImage);
			RegisterObject(mRotateCountImage);
			mStageTitle->SetEraseTime(2.f);
			mStageTitle->Excute();
			mRotateImage->Excute();
			mRotateCountImage->Excute();
		}

		RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, mScale);
		RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, mScale);
		RenderManager::GetInstance()->SetAlpha(eLayerType::BlendObject, 100);
		mPlayer->SetButterfly(mButterfly);
	}

	void GameScene::Update()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		const float RADIAN = 1.57079f;
		mPlayerIdleElapsed += DELTA_TIME;

		if (mPlayer->GetPlayerState() != ePlayerStateType::Idle)
		{
			mPlayerIdleElapsed = 0.f;
		}

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

		if (mbRotateScene && mPlayer->GetPlayerState() == ePlayerStateType::Idle)
		{
			const UINT CENTER_X = WinApp::GetWidth() / 2;
			const UINT CENTER_Y = WinApp::GetHeight() / 2;
			float cosValue;
			float sinValue;

			const float WEIGHT = DELTA_TIME * RADIAN * (mbRotateLeft ? -1 : 1);
			mRotateSceneElapsed += static_cast<float>(fabs(static_cast<double>(WEIGHT)));

			if (mRotateSceneElapsed < RADIAN / 2)
			{
				RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, static_cast<float>(mScale - 1.f + cosf(mRotateSceneElapsed)));
				RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, static_cast<float>(mScale - 1.f + cosf(mRotateSceneElapsed)));
			}
			else
			{
				RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, static_cast<float>(mScale - 1.f + sinf(mRotateSceneElapsed)));
				RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, static_cast<float>(mScale - 1.f + sinf(mRotateSceneElapsed)));
			}

			cosValue = cosf(WEIGHT);
			sinValue = sinf(WEIGHT);
			for (auto iter = mBoardObjects.begin(); iter != mBoardObjects.end(); ++iter)
			{
				(*iter)->Rotate(static_cast<float>(CENTER_X), static_cast<float>(CENTER_Y), cosValue, sinValue);
			}

			// 이 영역은 매프레임 델타타임으로 인한 가중치로 처리되는 공간
			if (mRotateSceneElapsed >= RADIAN)
			{
				// 이 영역은 회전이 끝나고 남은 변수를 초기화하고 정렬해주는 공간
				const float REMAINDER = (mRotateSceneElapsed - RADIAN) * (mbRotateLeft ? 1 : -1);
				mRotateSceneElapsed = 0;

				cosValue = cosf(REMAINDER);
				sinValue = sinf(REMAINDER);
				for (auto iter = mBoardObjects.begin(); iter != mBoardObjects.end(); ++iter)
				{
					(*iter)->Rotate(static_cast<float>(CENTER_X), static_cast<float>(CENTER_Y), cosValue, sinValue);
				}

				RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, mScale);
				RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, mScale);
				mbRotateScene = false;
				mbRotateObject = true;
			}

			for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				eObjectType objectType = (*iter)->GetObjectType();
				if (objectType != eObjectType::Player)
				{
					(*iter)->Update();
				}
			}

			return;
		}

		if (mbRotateObject && mPlayer->GetPlayerState() == ePlayerStateType::Idle)
		{
			float weight = DELTA_TIME * RADIAN * (mbRotateLeft ? 3 : -3);
			float cosValue;
			float sinValue;
			mRotateObjectElapsed += static_cast<float>(fabs(weight));

			if (mRotateObjectElapsed >= RADIAN)
			{
				weight += mRotateObjectElapsed - RADIAN * (mbRotateLeft ? -1 : 1);
				mbRotateObject = false;
				mRotateObjectElapsed = 0;
			}

			cosValue = cosf(weight);
			sinValue = sinf(weight);
			for (auto iter = mBoardObjects.begin(); iter != mBoardObjects.end(); ++iter)
			{
				Vector2 objectCenter = (*iter)->GetWorldRectangle().GetCenter();
				const UINT CENTER_X = static_cast<UINT>(objectCenter.GetX());
				const UINT CENTER_Y = static_cast<UINT>(objectCenter.GetY());

				(*iter)->Rotate(static_cast<float>(CENTER_X), static_cast<float>(CENTER_Y), cosValue, sinValue);
			}

			if (!mbRotateObject)
			{
				for (auto iter = mBoardObjects.begin(); iter != mBoardObjects.end(); ++iter)
				{
					(*iter)->RotateBoardIndex(mbRotateLeft);
					(*iter)->AlignWorldRectagle();
				}
			}

			return;
		}

		if (mRotateCount < mLimitRotateCount && mbStart && !mbRotateScene && !mbRotateObject && mPlayerIdleElapsed > 0.15f)
		{
			if (InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH)
			{
				mbRotateScene = true;
				mbRotateLeft = true;
				++mRotateCount;
				mRotateCountImage->SetSprite(&SpriteManager::GetInstance()->GetSprite(mNumbers[mLimitRotateCount - mRotateCount]));
			}
			else if (InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
			{
				mbRotateScene = true;
				mbRotateLeft = false;
				++mRotateCount;
				mRotateCountImage->SetSprite(&SpriteManager::GetInstance()->GetSprite(mNumbers[mLimitRotateCount - mRotateCount]));
			}
		}

		Scene::Update();
	}

	void GameScene::Render()
	{
		Scene::Render();

		if (mPlayer->GetStageClear())
		{
			mClearImage->Render();
		}
	}

	eSceneType GameScene::HandleScene()
	{
		if (mReturnButton->GetButtonState() == eButtonState::Click || InputManager::GetInstance()->GetKeyState(VK_ESCAPE) == eKeyState::PUSH)
		{
			return eSceneType::START;
		}
		if (mClearInterval >= mEndClearInterval || InputManager::GetInstance()->GetKeyState('N') == eKeyState::PUSH)
		{
			return mNextScene;
		}

		return mSceneType;
	}

	void GameScene::Exit()
	{
		Scene::Exit();
		mPlayer = nullptr;
		mBrick = nullptr;
		mButterfly = nullptr;
		mBoardObjects.clear();
		mClearImage = nullptr;
		mStageTitle = nullptr;
		mRotateImage = nullptr;
		RenderManager::GetInstance()->SetAlpha(eLayerType::BlendObject, 255);
		RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, 1.f);
		RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, 1.f);
	}
}

