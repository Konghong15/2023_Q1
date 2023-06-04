#include "SceneStart.h"
#include "Button.h"
#include "WinApp.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "Map.h"
#include "ConstantTable.h"
#include "TitlePlayer.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "Butterfly.h"

namespace catInWonderland
{
	SceneStart::SceneStart()
		: Scene(eSceneType::START)
		, mStartButton(nullptr)
		, mChallengeButton(nullptr)
		, mExitButton(nullptr)
		, mTitlePlayer(nullptr)
		, mbAlpha(false)
		, mAlphaElapsed(1.f)
		, mTitleButterfly(nullptr)
	{
	}

	void SceneStart::Enter()
	{
		SoundManager::GetInstance()->PlayMusic(eSoundList::StartBGM, eSoundChannel::BGM);
		//float x = WinApp::GetWidth() / 4;
		//float y = WinApp::GetHeight() / 4;
		//float w = WinApp::GetWidth() / 2; //- WinApp::GetWidth() / 8;
		//float h = WinApp::GetHeight() / 2;// -WinApp::GetHeight() / 8;
		Object* background = new Map(hRectangle(0, 0, static_cast<float>(WinApp::GetWidth()), static_cast<float>(WinApp::GetHeight())), BACKGROUND_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::MainTitle), eLayerType::Background);
		RegisterObject(background);

		mChallengeButton = new Button(TITLE_TEXT_CHALLENGE_RECT
			, TITLE_TEXT_CHALLENGE_SPRITE_RECT
			, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Challange)
			, eLayerType::Background);
		RegisterObject(mChallengeButton);

		/*Object* object = new Map(TITLE_TEXT_WORLD_RECT, TITLE_TEXT_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::TitleText));
		RegisterObject(object);*/

		mStartButton = new Button(TITLE_TEXT_START_RECT
			, TITLE_BUTTON_RECT
			, &SpriteManager::GetInstance()->GetSprite(eSpriteType::EnterButton)
			, eLayerType::BlendObject);
		RegisterObject(mStartButton);

		mExitButton = new Button(TITLE_TEXT_EXIT_RECT
			, TITLE_BUTTON_RECT
			, &SpriteManager::GetInstance()->GetSprite(eSpriteType::ExitButton)
			, eLayerType::BlendObject);
		RegisterObject(mExitButton);

		Scene::Enter();

		mTitlePlayer = new TitlePlayer(hRectangle(100, 600, 560, 960), eLayerType::NonBlendObject);
		RegisterObject(mTitlePlayer);

		// Butterfly(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite * sprite, eObjectType objectType, Object * interactionObjectOrNull, Player * player, eLayerType layerType, float maxOffset, bool bRed, bool bLeft, const Animator & animator);
		hRectangle butterflyRect(mTitlePlayer->GetWorldRectangle().GetTopLeft(), mTitlePlayer->GetWorldRectangle().GetCenter());
		mTitleButterfly = new Butterfly(butterflyRect, SpriteManager::GetInstance()->GetSpriteRectangle(eAnimationType::YellowButterfly, 0), &SpriteManager::GetInstance()->GetSprite(eSpriteType::Butterfly), eObjectType::Butterfly, mTitlePlayer, eLayerType::NonBlendObject, 0.f, true, mTitlePlayer->GetIsLeft(), SpriteManager::GetInstance()->GetAnimator(eAnimationType::YellowButterfly));
		RegisterObject(mTitleButterfly);

		mAlphaElapsed = 1.f;
		mbAlpha = false;
	}

	eSceneType SceneStart::HandleScene()
	{
		if (mTitlePlayer->GetWorldRectangle().GetTopRight().GetX() > 1920)
		{
			return eSceneType::STAGE01;
		}
		if (mChallengeButton->GetButtonState() == eButtonState::Click)
		{
			return eSceneType::STAGE06;
		}

		return mSceneType;
	}

	void SceneStart::Update()
	{
		Scene::Update();
		mTitlePlayer->Update();

		if (mbAlpha)
		{
			const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
			mAlphaElapsed -= DELTA_TIME;

			if (mAlphaElapsed > 0.f)
			{
				unsigned alpha = static_cast<unsigned int>(mAlphaElapsed * 255) % 256;

				RenderManager::GetInstance()->SetAlpha(eLayerType::BlendObject, alpha);
			}
			else
			{
				RenderManager::GetInstance()->SetAlpha(eLayerType::BlendObject, 0);
				mbAlpha = false;
			}
		}

		if (mStartButton->GetButtonState() == eButtonState::Click)
		{
			mbAlpha = true;
			mTitlePlayer->Excute();
			mTitlePlayer->SetAnimator(SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerMove));
			mTitleButterfly->SetInteractionObject(mChallengeButton);
		}

		if (mExitButton->GetButtonState() == eButtonState::Click)
		{
			// WM_QUIT 발생시키는 함수가 ㅣㅇㅆ어
			PostQuitMessage(0);
		}

	}

	void SceneStart::Exit()
	{
		Scene::Exit();
		mStartButton = nullptr;
		mExitButton = nullptr;
		mTitlePlayer = nullptr;
	}
}