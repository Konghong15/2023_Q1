#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRun.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Helper.h"

namespace hockman
{
	PlayerRun::PlayerRun()
		: PlayerState(ePlayerState::Run)
	{
	}

	void PlayerRun::Enter(Player* player)
	{
		mButtonVX = 0;
		player->SetAniIndex(0);
		player->SetAniElapsed(0.f);
		player->SetAniDuration(0.2f);
		player->SetIsAniLoop(true);
		player->SetUVRectangles(&mRunUVRects);
		player->SetUVRectangles(&mRunUVRects);
		player->SetUVRectangles(&mRunUVRects);
	}

	PlayerState* PlayerRun::HandleInputOrNull(Player* player)
	{
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == eKeyState::NONE
			&& InputManager::GetInstance()->GetKeyState(VK_RIGHT) == eKeyState::NONE)
		{
			return new PlayerIdle();
		}
		if (InputManager::GetInstance()->GetKeyState(VK_SPACE) != eKeyState::NONE)
		{
			return new PlayerJump();
		}

		int bitFlag = player->GetCollider()->GetCollisionBitFlag();
		if ((bitFlag & static_cast<int>(eObjectType::GROUND)) == 0)
		{
			return new PlayerJump();
		}
		return nullptr;
	}

	void PlayerRun::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		// handle ani
		{
			player->AddAniElapsed(DELTA_TIME);

			const float ELAPSED = player->GetAniElapsed();
			const float DURATION = player->GetAniDuration();
			if (ELAPSED >= DURATION)
			{
				player->AddAniIndex();
				player->SetAniElapsed(ELAPSED - DURATION);
			}
		}

		float accel = player->GetMoveSpeed() * DELTA_TIME;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			if (player->GetVX() > 0)
			{
				player->SetVX(0.f);
			}

			player->AddVX(-accel);
			player->SetIsRight(false);
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			if (player->GetVX() < 0)
			{
				player->SetVX(0.f);
			}

			player->AddVX(accel);
			player->SetIsRight(true);
		}

		const float speedX = player->GetVX() * DELTA_TIME;
		player->Move(speedX, 0);

		checkWall(player);
	}

	void PlayerRun::checkWall(Player* player)
	{
		std::vector<Collider*> objects = player->GetCollider()->GetCollisionObjects();

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			const Object& obj = (*iter)->GetOwnerObject();
			const eObjectType& objectType = obj.GetObjectType();

			if (objectType != eObjectType::GROUND)
			{
				continue;
			}

			const hRectangle& playerColRect = player->GetCollider()->GetWorldRectangle();
			const hRectangle& objColRect = obj.GetCollider()->GetWorldRectangle();
			const hRectangle intersectionRect = hRectangle::GetIntersection(playerColRect, objColRect);

			if (Helper::Equals(objColRect.GetTopLeft().GetY(), intersectionRect.GetTopLeft().GetY()))
			{
				continue;
			}

			if (Helper::Equals(playerColRect.GetTopLeft().GetX(), intersectionRect.GetTopLeft().GetX()))
			{
				player->Move(intersectionRect.GetSize().GetX(), 0);
				break;
			}
			else if (Helper::Equals(objColRect.GetTopLeft().GetX(), intersectionRect.GetTopLeft().GetX()))
			{
				player->Move(-intersectionRect.GetSize().GetX(), 0);
				break;
			}
		}
	}
}
