#include "Scene.h"
#include "Object.h"
#include "Button.h"
#include "ConstantTable.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SoundManager.h"

namespace catInWonderland
{
	bool Scene::mbSoundOn = true;

	Scene::Scene(eSceneType sceneType)
		: mSceneType(sceneType)
		, mSoundButton(nullptr)
		, mFadeInElapsed(1.f)
		, mbStart(false)
	{
		mObjects.reserve(OBJECT_CAPACITY);
	}

	Scene::~Scene()
	{
		Exit();
	}

	void Scene::Enter()
	{
		mSoundButton = new Button(hRectangle(48, 22, 193, 169), SET_BUTTON_RECT, &SpriteManager::GetInstance()->GetSprite(mbSoundOn ? eSpriteType::SoundOn : eSpriteType::SoundOff), eLayerType::Background);
		RegisterObject(mSoundButton);

		mbStart = false;
		mFadeInElapsed = 1.f;
	}

	void Scene::Update()
	{
		if (mSoundButton->GetButtonState() == eButtonState::Click)
		{
			if (mbSoundOn == true)
			{
				mbSoundOn = false;
				mSoundButton->SetSprite(&SpriteManager::GetInstance()->GetSprite(eSpriteType::SoundOff));

				SoundManager::GetInstance()->SetVolume(0.f);
			}
			else if (mbSoundOn == false)
			{
				mbSoundOn = true;
				mSoundButton->SetSprite(&SpriteManager::GetInstance()->GetSprite(eSpriteType::SoundOn));

				SoundManager::GetInstance()->SetVolume(0.5f);
			}
		}
		RenderManager::GetInstance()->SetPostProcessingColor(RGB(0, 0, 0));
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (mFadeInElapsed > 0.f && !mbStart)
		{
			mFadeInElapsed -= DELTA_TIME;

			if (mFadeInElapsed <= 0.f)
			{
				mFadeInElapsed = 0.f;
				mbStart = true;
			}

			RenderManager::GetInstance()->SetAlpha(eLayerType::PostProcessing, static_cast<unsigned int>(mFadeInElapsed * 255));
		}

		if (mbStart)
		{
			for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				(*iter)->Update();
			}
		}
	}

	void Scene::Render()
	{
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			(*iter)->Render();
		}
	}

	void Scene::Exit()
	{
		for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			Object* object = (*iter);
			delete object;
		}

		mObjects.clear();
		mSoundButton = nullptr;
		RenderManager::GetInstance()->SetAlpha(eLayerType::PostProcessing, 0);
	}
}