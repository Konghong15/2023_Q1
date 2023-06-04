#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerPlummet.h"
#include "PlayerAction.h"
#include "Player.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "BoardManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "BoardObject.h"
#include "eAnimaitonType.h"
#include "Butterfly.h"
#include "ChangeColorTile.h"

namespace catInWonderland
{
	PlayerIdle::PlayerIdle()
		: PlayerState(ePlayerStateType::Idle, SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerIdle))
	{
	}

	ePlayerStateType PlayerIdle::HandleStateOrNull(Player* player)
	{
		const std::vector<Object*>& objects = SceneManager::GetInstance()->GetCurrentScene().GetObjects();

		// 바닥이 존재하지 않으면 Plummet를 반환한다.
		int max = 0;
		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			Object* object = (*iter);
			eObjectType objectType = object->GetObjectType();

			if (objectType != eObjectType::Tile)
			{
				continue;
			}

			BoardObject* boardObject = static_cast<BoardObject*>(object);
			if (player->GetBoardX() != boardObject->GetBoardX())
			{
				continue;
			}

			int diff = static_cast<int>(boardObject->GetBoardY()) - static_cast<int>(player->GetBoardY());
			if (diff > max)
			{
				max = diff;
			}
		}

		bool bExistObtacle = max == 0;
		for (auto iter = objects.begin(); iter != objects.end(); iter++)
		{
			Object* obj = (*iter);
			if (obj->GetObjectType() != eObjectType::Obstacle)
			{
				continue;
			}

			BoardObject* boardObj = static_cast<BoardObject*>(obj);
			if (player->GetBoardY() + 1 == boardObj->GetBoardY() &&
				player->GetBoardX() == boardObj->GetBoardX())
			{
				bExistObtacle = true;
			}
		}

		if (!bExistObtacle)
		{
			return ePlayerStateType::Plummet;
		}

		if (InputManager::GetInstance()->GetKeyState('A') == eKeyState::PUSH && player->GetBoardX() > 0) // 내 왼쪽에 장애물이 있으면 return nullptr;
		{
			bool bExistTile = false;

			for (auto iter = objects.begin(); iter != objects.end(); iter++)
			{
				Object* object = (*iter);
				eObjectType objectType = object->GetObjectType();

				if (objectType == eObjectType::Obstacle)
				{
					BoardObject* boardObj = static_cast<BoardObject*>(object);

					if (player->GetBoardY() == boardObj->GetBoardY() &&
						player->GetBoardX() - 1 == boardObj->GetBoardX())
					{
						return mPlayerState;
					}
				}
				else if (objectType == eObjectType::Tile)
				{
					BoardObject* boardObj = static_cast<BoardObject*>(object);

					if (player->GetBoardY() == boardObj->GetBoardY() &&
						player->GetBoardX() - 1 == boardObj->GetBoardX())
					{
						bExistTile = true;
					}
				}
			}

			if (!bExistTile)
			{
				return mPlayerState;
			}

			return ePlayerStateType::Move;
		}

		if (InputManager::GetInstance()->GetKeyState('D') == eKeyState::PUSH && player->GetBoardX() < BoardManager::GetInstance()->GetBoardSize() - 1)
		{
			// 내 오른쪽에 장애물이 있으면 return nullptr;
			bool bExistTile = false;

			for (auto iter = objects.begin(); iter != objects.end(); iter++)
			{
				Object* object = (*iter);
				eObjectType objectType = object->GetObjectType();

				if (objectType == eObjectType::Obstacle)
				{
					BoardObject* boardObj = static_cast<BoardObject*>(object);

					if (player->GetBoardY() == boardObj->GetBoardY() &&
						player->GetBoardX() + 1 == boardObj->GetBoardX())
					{
						return mPlayerState;
					}
				}
				else if (objectType == eObjectType::Tile)
				{
					BoardObject* boardObj = static_cast<BoardObject*>(object);

					if (player->GetBoardY() == boardObj->GetBoardY() &&
						player->GetBoardX() + 1 == boardObj->GetBoardX())
					{
						bExistTile = true;
					}
				}
			}

			if (!bExistTile)
			{
				return mPlayerState;
			}

			return ePlayerStateType::Move;
		}

		if (InputManager::GetInstance()->GetKeyState('W') == eKeyState::PUSH)
		{
			return ePlayerStateType::Action;
		}

		return mPlayerState;
	}

	void PlayerIdle::Enter(Player* player)
	{
		PlayerState::Enter(player);
		HandleColorChange(player);

		if (player->GetPreventPlayerState() != ePlayerStateType::Action)
		{
			HandlePortal(player);
		}
	}
}