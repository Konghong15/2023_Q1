#include <windows.h>

#include "Stage10.h"
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

namespace catInWonderland
{
	Stage10::Stage10(const std::vector<BoardObjectInfo>& boardObjectInfos)
		: GameScene(eSceneType::STAGE10, eSceneType::CutScene03, 8u, 5u, 1.f, eSpriteType::StageName10, eSpriteType::PurpleTile, boardObjectInfos)
	{
	}

	void Stage10::CreateBoardObject()
	{
		auto iter = mBoardObjectInfos.begin();

		mPlayer = static_cast<Player*>(Creator::CreateBoardObject(*iter++));
		mBrick = static_cast<Brick*>(Creator::CreateBoardObject(*iter++));
		Portal* portal0 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));
		Portal* portal1 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));
		Portal* portal2 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));
		Portal* portal3 = static_cast<Portal*>(Creator::CreateBoardObject(*iter++));

		portal0->SetConnectedPortal(portal1);
		portal1->SetConnectedPortal(portal0);
		portal2->SetConnectedPortal(portal3);
		portal3->SetConnectedPortal(portal2);

		for (; iter != mBoardObjectInfos.end(); ++iter)
		{
			RegisterBoardObject(Creator::CreateBoardObject(*iter));
		}

		mButterfly = new Butterfly(hRectangle(mPlayer->GetWorldRectangle().GetTopLeft(), mPlayer->GetWorldRectangle().GetCenter()), BUTTER_FLY_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Butterfly), eObjectType::Butterfly, mPlayer, eLayerType::NonBlendObject, 0.f, true, mPlayer->GetIsLeft(), SpriteManager::GetInstance()->GetAnimator(eAnimationType::RedButterfly));
		RegisterBoardObject(mBrick);
		RegisterBoardObject(portal0);
		RegisterBoardObject(portal1);
		RegisterBoardObject(portal2);
		RegisterBoardObject(portal3);
		RegisterBoardObject(mPlayer);
		RegisterObject(mButterfly);
	}

	void Stage10::Enter()
	{
		SoundManager::GetInstance()->PlayMusic(eSoundList::Stage345BGM, eSoundChannel::BGM);
		Object* object = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Stage05), eLayerType::Background);
		RegisterObject(object);
		GameScene::Enter();
	}
}