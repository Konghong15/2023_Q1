#include <cassert>
#include <Windows.h>

#include "TitleScene.h"
#include "ObjectManager.h"
#include "Button.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "eSceneType.h"
#include "InputManager.h"

namespace hongpireSurvivors
{
	TitleScene::TitleScene(eSpriteType background, COORD sceneSize, COORD camaraPos)
		: Scene(sceneSize, camaraPos)
		, mBGSpriteType(background)
		, mSelect(eSelect::START)
	{
	}

	void TitleScene::Enter()
	{
		ObjectManager::GetInstance()->Init();
		SoundManager::GetInstance()->Play(eSound::TITLE_BGM);
	}

	void TitleScene::Frame()
	{
		RenderManager::GetInstance()->DrawMap(eSpriteType::TITLE_BG_0, { 400, 70 }, mCamaraPos, RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE));
		RenderManager::GetInstance()->DrawMap(eSpriteType::TITLE_BG_1, mSceneSize, mCamaraPos, RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::WHITE));

		bool isLeft = InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::PUSH;
		bool isRight = InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::PUSH;
		bool isSelect = InputManager::GetInstance()->GetKeyState(VK_RETURN) == eKeyState::PUSH;

		switch (mSelect)
		{
		case hongpireSurvivors::eSelect::START:
			RenderManager::GetInstance()->DrawRect(160, 40, 65, 20, '@', RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::GREEN));
			if (isSelect)
			{
				SceneManager::GetInstance()->Enter(eSceneType::GAME);
			}
			else if (isLeft)
			{
				mSelect = eSelect::EXIT;
			}
			else if (isRight)
			{
				mSelect = eSelect::OPTION;
			}
			break;
		case hongpireSurvivors::eSelect::OPTION:
			RenderManager::GetInstance()->DrawRect(235, 40, 75, 20, '@', RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::GREEN));
			if (isSelect)
			{
				// 옵션창이동
			}
			else if (isLeft)
			{
				mSelect = eSelect::START;
			}
			else if (isRight)
			{
				mSelect = eSelect::EXIT;
			}
			break;
		case hongpireSurvivors::eSelect::EXIT:
			RenderManager::GetInstance()->DrawRect(320, 40, 50, 20, '@', RenderManager::GetColor(eConsoleColor::BLACK, eConsoleColor::GREEN));
			if (isSelect)
			{
				// 종료
			}
			else if (isLeft)
			{
				mSelect = eSelect::OPTION;
			}
			else if (isRight)
			{
				mSelect = eSelect::START;
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	void TitleScene::Exit()
	{
		ObjectManager::GetInstance()->Release();
		SoundManager::GetInstance()->Stop(eSound::TITLE_BGM);
	}
}