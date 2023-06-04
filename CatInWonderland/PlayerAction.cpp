#include "PlayerAction.h"
#include "PlayerIdle.h"
#include "Player.h"
#include "Brick.h"
#include "Butterfly.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "BoardManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "ConstantTable.h"

namespace catInWonderland
{
	PlayerAction::PlayerAction()
		: PlayerState(ePlayerStateType::Action, SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerAction))
		, mBrick(nullptr)
		, mDistance(0.f)
		, mElapsed(0.f)
		, mStateEndTime(PLAYER_ACTION_TIME)
	{
	}

	ePlayerStateType PlayerAction::HandleStateOrNull(Player* player)
	{
		if (mElapsed >= 1.f)
		{
			return ePlayerStateType::Idle;
		}

		return mPlayerState;
	}

	void PlayerAction::Enter(Player* player)
	{
		PlayerState::Enter(player);

		SoundManager::GetInstance()->PlayMusic(eSoundList::CatGoalEffect, eSoundChannel::Effect);

		mElapsed = 0.f;
		mDistance = 0.f;
		mBrick = nullptr;

		const std::vector<Object*>& objects = SceneManager::GetInstance()->GetCurrentScene().GetObjects();
		for (auto iter = objects.begin(); iter != objects.end(); iter++)
		{
			Object* obj = (*iter);
			eObjectType objectType = obj->GetObjectType();

			if (objectType == eObjectType::RedBrick
				|| objectType == eObjectType::BlueBrick)
			{
				Brick* brick = static_cast<Brick*>(obj);

				if (brick->GetBoardX() == player->GetBoardX()
					&& brick->GetBoardY() < player->GetBoardY()
					&& brick->GetIsRed() != player->GetIsRed())
				{
					mBrick = brick;
					const unsigned int MOVED_Y = static_cast<unsigned int>(player->GetBoardY() - brick->GetBoardY());
					mDistance = MOVED_Y * BoardManager::GetInstance()->GetCellSize();
				}
			}
		}

		if (mBrick != nullptr)
		{
			for (auto iter = objects.begin(); iter != objects.end(); iter++)
			{
				// 벽돌과 플레이어 사이에 장애물이 있다면? mBrick = nullptr로 변환 break;
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

				assert(mBrick != nullptr);
				if (player->GetBoardY() > boardObj->GetBoardY() && mBrick->GetBoardY() < boardObj->GetBoardY())
				{
					mBrick = nullptr;
					break;
				}
			}
		}
	}

	void PlayerAction::Update(Player* player)
	{
		PlayerState::Update(player);

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime() / mStateEndTime;
		mElapsed += DELTA_TIME;

		if (mBrick == nullptr)
		{
			return;
		}
		if (mBrick->GetBoardY() == player->GetBoardY())
		{
			return;
		}

		float currentDistance = mDistance * DELTA_TIME;
		mBrick->MoveInWorld(0.f, currentDistance);
	}

	void PlayerAction::Exit(Player* player)
	{
		if (mBrick == nullptr)
		{
			return;
		}

		const unsigned int MOVED_Y = static_cast<unsigned int>(player->GetBoardY() - mBrick->GetBoardY());

		float remaider = mElapsed - 1.0f;
		mBrick->MoveInBoard(0, MOVED_Y);
		mBrick->MoveInWorld(0.f, -mDistance * remaider);
		mBrick->AlignWorldRectagle();
		player->SetStageClear(true);
		mBrick = nullptr;
	}
}
