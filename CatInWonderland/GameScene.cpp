#include "GameScene.h"
#include "hRectangle.h"
#include "WinApp.h"
#include "BoardManager.h"
#include "RenderManager.h"
#include "Player.h"

namespace catInWonderland
{
	GameScene::GameScene(size_t width, size_t height)
		: Scene(width, height)
	{
	}

	void GameScene::Enter()
	{
		BoardManager::GetInstance()->SetBoardSize(3u);

		Object* obj = new Player(BoardManager::GetInstance()->GetWorldRect(1, 2), 1, 2);
		Spawn(obj);
	}

	void GameScene::Frame()
	{
		const size_t BOARD_SIZE = BoardManager::GetInstance()->GetBoardSize();

		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				RenderManager::GetInstance()->DrawRect(BoardManager::GetInstance()->GetWorldRect(j, i), RGB(0, 0, 0));
			}
		}

		Scene::Frame();
	}
}