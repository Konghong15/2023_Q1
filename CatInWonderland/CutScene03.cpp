#include <windows.h>

#include "CutScene03.h"
#include "Map.h"
#include "WinApp.h"
#include "SpriteManager.h"
#include "ConstantTable.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SceneLoader.h"
#include "RenderManager.h"

namespace catInWonderland
{
	CutScene03::CutScene03()
		:CutScene(eSceneType::CutScene03)
		, mMapSprites{ nullptr, }
		, mSpriteIndex(0u)
		, mElapsed(0.f)
		, mbEnd(false)
	{

	}

	eSceneType CutScene03::HandleScene()
	{
		if (mbEnd)
		{
			return eSceneType::START;
		}

		return mSceneType;
	}

	void CutScene03::Enter()
	{
		mMap = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_01), eLayerType::Background);

		mSpriteIndex = 0u;
		mElapsed = 0.f;
		mbEnd = false;

		mMapSprites[0] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_01);
		mMapSprites[1] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_02);
		mMapSprites[2] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_03);
		mMapSprites[3] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_04);
		mMapSprites[4] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene03_05);
		RegisterObject(mMap);

		CutScene::Enter();
	}

	void CutScene03::Update()
	{
		CutScene::Update();
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapsed += DELTA_TIME;
		if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::PUSH)
		{
			++mSpriteIndex;

			if (mSpriteIndex >= SPRITE_SIZE)
			{
				mbEnd = true;
			}
			else
			{
				mMap->SetSprite(mMapSprites[mSpriteIndex]);
			}
		}
	}

	void CutScene03::Exit()
	{
		mMap = nullptr;
		mbEnd = false;
		mElapsed = 0.f;
		ZeroMemory(mMapSprites, sizeof(mMapSprites));
		RenderManager::GetInstance()->SetAlpha(eLayerType::PostProcessing, 0);

		CutScene::Exit();
	}
}