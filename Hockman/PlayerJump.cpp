#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerRun.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"

namespace hockman
{
	PlayerJump::PlayerJump()
		: PlayerState(ePlayerState::Jump)
		, mIsDown(false)
		, mIsEnd(false)
	{
	}

	void PlayerJump::Enter(Player* player)
	{
		player->SetVY(-1500.f);
		player->SetAniIndex(0);
		player->SetAniElapsed(0.f);
		player->SetAniDuration(0.2f);
		player->SetIsAniLoop(false);
		player->SetUVRectangles(&mJumpUVRects);
	}

	PlayerState* PlayerJump::HandleInputOrNull(Player* player)
	{
		if (mIsEnd)
		{
			return new PlayerIdle();
		}

		return nullptr;
	}

	void PlayerJump::Update(Player* player)
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (player->GetVY() > 0)
		{
			player->SetAniIndex(1);
			mIsDown = true;
			player->AddVY(player->GetGravity() * DELTA_TIME * 2);
		}
		else
		{
			player->AddVY(player->GetGravity() * DELTA_TIME);
		}

		float distanceX = player->GetMoveSpeed() * DELTA_TIME * 0.8f;
		const float distanceY = player->GetVY() * DELTA_TIME;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			distanceX *= -1.f;
			player->SetIsRight(false);
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			player->SetIsRight(true);
		}
		else
		{
			distanceX = 0.f;
		}

		player->Move(distanceX, distanceY);

		const int GROUND = 800;

		const hRectangle& playerRect = player->GetRectangle();
		const Vector2& pos = playerRect.GetPos();
		const Vector2& size = playerRect.GetSize();

		const int BOTTOM_Y = pos.GetY() + size.GetY();
		if (BOTTOM_Y > GROUND)
		{
			player->Move(0, GROUND - BOTTOM_Y);
			mIsEnd = true;
		}

		std::vector<Collider*> objects = player->GetCollider()->GetCollisionObjects();
		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			const Object& obj = (*iter)->GetOwnerObject();
			if (obj.GetObjectType() == eObjectType::GROUND)
			{
				const hRectangle& playerRect = player->GetRectangle();
				const hRectangle& objRect = obj.GetRectangle();

				hRectangle intersectionRect = hRectangle::GetIntersection(objRect, playerRect);


				if (intersectionRect.GetPos().GetY() == playerRect.GetPos().GetY())
				{
					player->SetVY(0.f);
					break;
				}
				else if (intersectionRect.GetBottomRight().GetY() == playerRect.GetBottomRight().GetY())
				{
					player->Move(0, objRect.GetPos().GetY() - BOTTOM_Y);
					mIsEnd = true;
				}
			}
		}
	}
}