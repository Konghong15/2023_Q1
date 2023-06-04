#include <windows.h>

#include "Stage05.h"
#include "Map.h"
#include "WinApp.h"
#include "SpriteManager.h"
#include "BoardManager.h"
#include "Brick.h"
#include "Butterfly.h"
#include "Player.h"
#include "ConstantTable.h"
#include "SoundManager.h"
#include "Button.h"
#include "Tile.h"
#include "BoardObjectInfo.h"
#include "SceneLoader.h"
#include "Creator.h"
#include "PlummetObject.h"
#include "RenderManager.h"
#include "Portal.h"
#include "TimeManager.h"
#include "InputManager.h"

namespace catInWonderland
{
	Stage05::Stage05(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE05, eSceneType::CutScene03, 10u, 7u, 1.0f, eSpriteType::StageName5, eSpriteType::PurpleTile, boardObjectInfos)
	{
	}

	void Stage05::CreateBoardObject()
	{
		auto iter = mBoardObjectInfos.begin();

		mPlayer = static_cast<Player*>(Creator::CreateBoardObject(*iter++));
		mBrick = static_cast<Brick*>(Creator::CreateBoardObject(*iter++));
		Portal* portal0 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));
		Portal* portal1 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));

		portal0->SetConnectedPortal(portal1);
		portal1->SetConnectedPortal(portal0);

		for (; iter != mBoardObjectInfos.end(); ++iter)
		{
			RegisterBoardObject(Creator::CreateBoardObject(*iter));
		}

		mButterfly = new Butterfly(hRectangle(mPlayer->GetWorldRectangle().GetTopLeft(), mPlayer->GetWorldRectangle().GetCenter()), BUTTER_FLY_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Butterfly), eObjectType::Butterfly, mPlayer, eLayerType::NonBlendObject, 0.f, true, mPlayer->GetIsLeft(), SpriteManager::GetInstance()->GetAnimator(eAnimationType::RedButterfly));
		RegisterBoardObject(mBrick);
		RegisterBoardObject(portal0);
		RegisterBoardObject(portal1);
		RegisterBoardObject(mPlayer);
		RegisterObject(mButterfly);
	}

	void Stage05::CreateTileObject()
	{
		BoardManager::GetInstance()->CreateBoard(mBoardSize, 170, 0);

		BoardObject* boardObject;
		for (unsigned int i = 0; i < mBoardSize / 2; ++i)
		{
			for (unsigned int j = 0; j < mBoardSize / 2; ++j)
			{
				boardObject = new Tile(BoardManager::GetInstance()->GetWorldRectangle(i, j),
					TILE_RECT,
					&SpriteManager::GetInstance()->GetSprite(eSpriteType::PurpleTile),
					eLayerType::BlendObject,
					i, j);

				RegisterBoardObject(boardObject);

				boardObject = new Tile(BoardManager::GetInstance()->GetWorldRectangle(i + mBoardSize / 2, j + mBoardSize / 2),
					TILE_RECT,
					&SpriteManager::GetInstance()->GetSprite(eSpriteType::PurpleTile),
					eLayerType::BlendObject,
					i + mBoardSize / 2, j + mBoardSize / 2);

				RegisterBoardObject(boardObject);
			}
		}
	}

	void Stage05::Enter()
	{
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage345BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage05), eLayerType::Background);
		RegisterObject(object);
		CreateGuideButterfly(eAnimationType::BlueButterfly, eSpriteType::Guide51, eSpriteType::Guide52);
		ExcuteButterfly(0);

		GameScene::Enter();
		mPlayer->SetIsRed(false);
	}

	void Stage05::Update()
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

	void Stage05::Exit()
	{
		RenderManager::GetInstance()->SetScale(eLayerType::BlendObject, 1.f);
		RenderManager::GetInstance()->SetScale(eLayerType::NonBlendObject, 1.f);
		RenderManager::GetInstance()->SetAlpha(eLayerType::BlendObject, 100);
		GameScene::Exit();
	}
}