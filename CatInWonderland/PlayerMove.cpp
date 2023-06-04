#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "Player.h"
#include "BoardManager.h"
#include "SpriteManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Butterfly.h"
#include "InputManager.h"
#include "ConstantTable.h"
#include "ChangeColorTile.h"
#include "Portal.h"
#include "Vector2.h"
#include "PlayerPlummet.h"

namespace catInWonderland
{
	PlayerMove::PlayerMove()
		: PlayerState(ePlayerStateType::Move, SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerMove))
		, mDistance(0.f)
		, mElapsed(0.f)
		, mStateEndTime(PLAYER_MOVE_TIME)
		, mMaxOffset(0.f)
		, mMoveX(0)
	{
	}

	ePlayerStateType PlayerMove::HandleStateOrNull(Player* player)
	{
		if (mElapsed >= 1.0f)
		{
			const std::vector<Object*>& objects = SceneManager::GetInstance()->GetCurrentScene().GetObjects();

			int max = 0;
			for (auto iter = objects.begin(); iter != objects.end(); ++iter)
			{
				Object* object = (*iter);
				if (object->GetObjectType() != eObjectType::Tile)
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

			return ePlayerStateType::Idle;
		}

		return mPlayerState;
	}

	void PlayerMove::Enter(Player* player)
	{
		PlayerState::Enter(player);

		memset(&mWorldRectangle, 0, sizeof(hRectangle));
		mDistance = 0;
		mElapsed = 0;
		mMaxOffset = 0;
		mMoveX = 0;

		if (InputManager::GetInstance()->GetKeyState('A') == eKeyState::PUSH)
		{
			player->SetIsLeft(true);
			mMoveX = -1;
			mDistance = -BoardManager::GetInstance()->GetCellSize();
		}
		else if (InputManager::GetInstance()->GetKeyState('D') == eKeyState::PUSH)
		{
			player->SetIsLeft(false);
			mMoveX = 1;
			mDistance = BoardManager::GetInstance()->GetCellSize();
		}

		player->MoveInBoard(mMoveX, 0);
	}

	void PlayerMove::Update(Player* player)
	{
		PlayerState::Update(player);

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime() / mStateEndTime;
		float currentDistance = mDistance * DELTA_TIME;
		mElapsed += DELTA_TIME;

		player->MoveInWorld(currentDistance, 0.f);
	}

	void PlayerMove::Exit(Player* player)
	{
		float remaider = mElapsed - 1.0f;
		player->MoveInWorld(-mDistance * remaider, 0.f);
		player->SetIsRed(!player->GetIsRed());

		PlayerState::Exit(player);
	}
}
