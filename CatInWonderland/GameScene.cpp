#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "GameScene.h"
#include "hRectangle.h"
#include "WinApp.h"
#include "BoardManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Player.h"

namespace catInWonderland
{
	GameScene::GameScene()
		: Scene()
		, mbRotate(false)
		, mbLeft(false)
		, mRotationEnd(1.5708f)
		, mElapsed(0.f)
	{
	}

	void GameScene::Enter()
	{
		BoardManager::GetInstance()->SetBoardSize(3u);

		Object* obj = new Player(BoardManager::GetInstance()->GetWorldRect(0, 0), 0, 0);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(0, 1), 0, 1);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(0, 2), 0, 2);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(1, 0), 1, 0);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(1, 1), 1, 1);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(1, 2), 1, 2);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(2, 0), 2, 0);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(2, 1), 2, 1);
		Spawn(obj);
		obj = new Player(BoardManager::GetInstance()->GetWorldRect(2, 2), 2, 2);
		Spawn(obj);
	}

	void GameScene::Frame()
	{
		if (mbRotate)
		{
			const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
			float radian = DELTA_TIME * mRotationEnd;
			mElapsed += radian;

			if (mbLeft)
			{
				radian *= -1;
			}

			for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				(*iter)->Rotate(WinApp::GetWidth() / 2, WinApp::GetHeight() / 2, radian);
			}

			if (mRotationEnd < mElapsed)
			{
				mbRotate = false;

				for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
				{
					(*iter)->RotateIndex(mbLeft);
					char buffer[64];
					sprintf(buffer, "{ %d, %d }", (*iter)->GetIndexX(), (*iter)->GetIndexY());
					OutputDebugStringA(buffer);
				}
				OutputDebugStringA("\n");
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
			{
				mElapsed = 0.f;
				mbRotate = true;
				mbLeft = false;
			}
			else if (InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH)
			{
				mElapsed = 0.f;
				mbRotate = true;
				mbLeft = true;
			}

			Scene::Frame();
		}

		Scene::Render();
	}
}