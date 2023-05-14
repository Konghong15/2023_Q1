#define _CRT_SECURE_NO_WARNINGS

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
	PlayerJump::PlayerJump()
		: PlayerState(ePlayerState::Jump)
		, mIsDown(false)
		, mIsEnd(false)
	{
	}

	void PlayerJump::Enter(Player* player)
	{
		if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::NONE)
		{
			player->SetAniIndex(1);
		}
		else
		{
			player->SetVY(-1500.f);
			player->SetAniIndex(0);
		}
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
			mIsDown = true;
			player->SetAniIndex(1);
			player->SetAniIndexY(0);
		}

		player->AddVY(player->GetGravity() * DELTA_TIME);
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			player->SetIsRight(false);
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			player->SetIsRight(true);
		}

		const float speedY = player->GetVY() * DELTA_TIME;
		const float speedX = player->GetVX() * DELTA_TIME;
		player->Move(speedX, speedY);

		checkGround(player);
	}

	void PlayerJump::checkGround(Player* player)
	{
		std::vector<Collider*> objects = player->GetCollider()->GetCollisionObjects();

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			const Object& curObject = (*iter)->GetOwnerObject();
			const eObjectType& curObjectType = curObject.GetObjectType();

			if (curObjectType != eObjectType::GROUND)
			{
				continue;
			}

			const hRectangle& playerColRect = player->GetCollider()->GetWorldRectangle();
			const hRectangle& playerPrevColRect = player->GetCollider()->GetPrevWorldRectangle();
			const hRectangle& objColRect = curObject.GetCollider()->GetWorldRectangle();
			const hRectangle intersectionRect = hRectangle::GetIntersection(playerColRect, objColRect);

			if (Helper::Equals(playerColRect.GetTopLeft().GetY(), intersectionRect.GetTopLeft().GetY())
				&& (playerPrevColRect.GetTopLeft().GetY() - objColRect.GetBottomRight().GetY()) > -50.f)
			{
				player->Move(0, intersectionRect.GetSize().GetY());
				player->SetVY(0.f);
			}
			else if (Helper::Equals(objColRect.GetTopLeft().GetY(), intersectionRect.GetTopLeft().GetY())
				&& playerPrevColRect.GetBottomRight().GetY() > objColRect.GetTopLeft().GetY())
			{
				const float speedY = player->GetVY() * TimeManager::GetInstance()->GetDeltaTime();
				float prevY = player->GetRectangle().GetTopLeft().GetY();

				float y = intersectionRect.GetSize().GetY() + speedY;
				player->Move(0, -y);
				mIsEnd = true;

				float curY = player->GetRectangle().GetTopLeft().GetY();
				char buf[128];
				sprintf(buf, "prevY : %f, curY : %f, y : %f\n", prevY, curY, y);
				OutputDebugStringA(buf);
			}
			else if (playerPrevColRect.GetBottomRight().GetY() > objColRect.GetTopLeft().GetY())
			{
				player->SetVX(0.f);
				if (Helper::Equals(objColRect.GetTopRight().GetX(), intersectionRect.GetTopRight().GetX()))
				{
					player->Move(intersectionRect.GetSize().GetX() + 1, 0);
				}
				else if (Helper::Equals(objColRect.GetTopLeft().GetX(), intersectionRect.GetTopLeft().GetX()))
				{
					player->Move(-intersectionRect.GetSize().GetX() - 1, 0);
				}
			}
		}
	}
}