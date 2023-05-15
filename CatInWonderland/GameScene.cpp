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
		static bool bRotate = false;
		static bool bLeft = false;

		static float arrival = 0.f;
		static float elapsed = 0.f;

		if (InputManager::GetInstance()->GetKeyState('E') == eKeyState::PUSH)
		{
			elapsed = 0.f;
			arrival = 1.5708f;
			bRotate = true;
			bLeft = false;
		}
		else if (InputManager::GetInstance()->GetKeyState('Q') == eKeyState::PUSH)
		{
			elapsed = 0.f;
			arrival = 1.5708f;
			bRotate = true;
			bLeft = true;
		}

		if (bRotate)
		{
			const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
			elapsed += DELTA_TIME;
			float curRadian = DELTA_TIME;

			if (bLeft)
			{
				curRadian *= -1;
			}

			for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				(*iter)->Rotate(curRadian, WinApp::GetWidth() / 2, WinApp::GetHeight() / 2);
			}

			if (arrival < elapsed)
			{
				bRotate = false;

				float remaider = arrival - elapsed;

				if (bLeft)
				{
					remaider *= -1;
				}

				for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
				{
					(*iter)->Rotate(remaider, WinApp::GetWidth() / 2, WinApp::GetHeight() / 2);
				}
			}
		}

		Scene::Frame();
	}
}