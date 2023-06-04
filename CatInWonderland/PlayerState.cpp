#include <vector>

#include "PlayerState.h"
#include "TimeManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "Portal.h"
#include "BoardManager.h"
#include "ChangeColorTile.h"
#include "Butterfly.h"

namespace catInWonderland
{
	PlayerState::PlayerState(ePlayerStateType playerState, const Animator& animator)
		: mPlayerState(playerState)
		, mAnimator(animator)
	{
	}

	void PlayerState::Enter(Player* player)
	{
		player->SetSpriteRectangle(mAnimator.GetSpriteRectangle(0));
	}

	void PlayerState::Update(Player* player)
	{
		mAnimator.Update(player);
	}

	void PlayerState::Exit(Player* player)
	{
		player->AlignWorldRectagle();
	}

	void PlayerState::HandlePortal(Player* player)
	{
		const std::vector<Object*>& objects = SceneManager::GetInstance()->GetCurrentScene().GetObjects();
		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			Object* object = *iter;

			if (object->GetObjectType() != eObjectType::YellowPortal && object->GetObjectType() != eObjectType::PurplePortal)
			{
				continue;
			}

			Portal* portal = static_cast<Portal*>(object);
			if (portal->CompareBoardIndex(*player))
			{
				const Portal& connectedPortal = portal->GetConnectedPortal();
				const unsigned int MOVED_X = static_cast<unsigned int>(connectedPortal.GetBoardX());
				const unsigned int MOVED_Y = static_cast<unsigned int>(connectedPortal.GetBoardY());
				player->SetBoardIndex(MOVED_X, MOVED_Y);
				player->SetWorldRectangle(BoardManager::GetInstance()->GetWorldRectangle(MOVED_X, MOVED_Y));

				break;
			}
		}
	}

	void PlayerState::HandleColorChange(Player* player)
	{
		const std::vector<Object*>& objects = SceneManager::GetInstance()->GetCurrentScene().GetObjects();

		for (auto iter = objects.begin(); iter != objects.end(); iter++)
		{
			Object* object = (*iter);
			eObjectType objectType = object->GetObjectType();

			if (objectType != eObjectType::BlueChangeColorTile && objectType != eObjectType::RedChangeColorTile)
			{
				continue;
			}

			ChangeColorTile* changeColorTile = static_cast<ChangeColorTile*>(object);

			if (changeColorTile->CompareBoardIndex(*player))
			{
				player->GetButterfly()->SetIsRed(changeColorTile->GetIsRed());
				break;
			}
		}
	}
}