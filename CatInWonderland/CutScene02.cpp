#include <windows.h>

#include "CutScene02.h"
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
	CutScene02::CutScene02()
		:CutScene(eSceneType::CutScene02)
		, mMapSprites{ nullptr, }
		, mSpriteIndex(0u)
		, mElapsed(0.f)
		, mbEnd(false)
	{

	}

	eSceneType CutScene02::HandleScene()
	{
		if (mbEnd)
		{
			return eSceneType::STAGE05;
		}

		return mSceneType;
	}

	void CutScene02::Enter()
	{
		mMap = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene02_01),eLayerType::Background);

		mSpriteIndex = 0u;
		mElapsed = 0.f;
		mbEnd = false;

		mMapSprites[0] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene02_01);
		mMapSprites[1] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene02_02);
		mMapSprites[2] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene02_03);
		mMapSprites[3] = &SpriteManager::GetInstance()->GetSprite(eSpriteType::CutScene02_04);
		RegisterObject(mMap);

		CutScene::Enter();
	}

	void CutScene02::Update()
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

	void CutScene02::Exit()
	{
		mMap = nullptr;
		mbEnd = false;
		mElapsed = 0.f;
		ZeroMemory(mMapSprites, sizeof(mMapSprites));
		RenderManager::GetInstance()->SetAlpha(eLayerType::PostProcessing, 0);

		CutScene::Exit();
	}
}