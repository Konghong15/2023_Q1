#include "PlayerPlummet.h"
#include "BoardManager.h"
#include "SpriteManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "PlayerIdle.h"
#include "ConstantTable.h"
#include "Obstacle.h"
#include "ChangeColorTile.h"
#include "Butterfly.h"

namespace catInWonderland
{
	PlayerPlummet::PlayerPlummet()
		: PlayerState(ePlayerStateType::Plummet, SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerPlummet))
		, mDistance(0.f)
		, mElapsed(0.f)
		, mStateEndTime(PLAYER_PLUMMET_TIME)
		, mMovedBoardY(0u)
	{
	}

	ePlayerStateType PlayerPlummet::HandleStateOrNull(Player* player)
	{
		if (mElapsed >= 1.f)
		{
			return ePlayerStateType::Idle;
		}

		return mPlayerState;
	}

	void PlayerPlummet::Enter(Player* player)
	{
		PlayerState::Enter(player);

		mElapsed = 0.f;
		mDistance = 0.f;
		mMovedBoardY = 0;

		SoundManager::GetInstance()->PlayMusic(eSoundList::CatDropEffect, eSoundChannel::Effect);
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

		int min = max;

		for (auto iter = objects.begin(); iter != objects.end(); iter++)
		{
			Object* obj = (*iter);
			if (obj->GetObjectType() != eObjectType::Obstacle)
			{
				continue;
			}

			BoardObject* boardObj = static_cast<BoardObject*>(obj);
			if (player->GetBoardX() != boardObj->GetBoardX())
			{
				continue;
			}
			if (player->GetBoardY() >= boardObj->GetBoardY())
			{
				continue;
			}

			if (boardObj->GetBoardY() - player->GetBoardY() - 1 < min)
			{
				min = static_cast<int>(boardObj->GetBoardY() - player->GetBoardY() - 1);
			}
		}
		// 장애물이 생길 경우 그 바닥 위로 판정 바꿔야 함

		mMovedBoardY = min;
		mDistance = BoardManager::GetInstance()->GetCellSize() * mMovedBoardY;
		//player->SetAnimator(SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerPlummet));
	}

	void PlayerPlummet::Update(Player* player)
	{
		PlayerState::Update(player);

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime() / (mStateEndTime * mMovedBoardY);
		float currentDistance = mDistance * DELTA_TIME;
		mElapsed += DELTA_TIME;

		player->MoveInWorld(0.f, currentDistance);
	}

	void PlayerPlummet::Exit(Player* player)
	{
		float remaider = mElapsed - 1.0f;
		player->MoveInWorld(0.f, -mDistance * remaider);

		for (int i = 0; i < mMovedBoardY; ++i)
		{
			player->MoveInBoard(0, 1);
			HandleColorChange(player);
		}

		PlayerState::Exit(player);
	}
}
