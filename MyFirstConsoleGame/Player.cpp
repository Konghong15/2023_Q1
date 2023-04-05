#pragma once

#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Projectile.h"
#include "Collider.h"
#include "ColliderManager.h"

namespace hongpireSurvivors
{
	Player::Player(COORD pos, COORD size, eSpriteType spriteType)
		: Object(pos, size, spriteType, eObjectType::PLAYER, true)
		, mCanMove(true)
		, mCanAttack(true)
		, mCanJump(true)
		, mElapsed(0.f)
		, mAttackElapsed(0.f)
		, mJumpForce(0.f)
	{
	}

	void Player::Frame()
	{
		if (!mCanMove)
		{
			mElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mElapsed >= 0.01f)
			{
				mElapsed -= 0.01f;
				mCanMove = true;
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
			{
				--mPos.X;
				mCanMove = false;
			}
			else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
			{
				++mPos.X;
				mCanMove = false;
			}

			if (InputManager::GetInstance()->GetKeyState(VK_UP) != eKeyState::NONE)
			{
				mJumpForce = 1.0f;
				mCanJump = false;
			}
		}

	/*	if (mCanJump)
		{
			if (InputManager::GetInstance()->GetKeyState(VK_UP) != eKeyState::NONE)
			{
				mJumpForce = 1.0f;
				mCanJump = false;
			}
		}
		else
		{
			if (mPos.Y + mSize.Y == 67)
			{
				mJumpForce = 0.f;
				mCanJump = true;
			}
		}

		if (mJumpForce >= 0.f && mCanMove)
		{
			mJumpForce -= TimeManager::GetInstance()->GetDeltaTime();
			++mPos.Y;
			--mJumpForce;
		}
		else
		{
			--mPos.Y;
		}*/

		if (!mCanAttack)
		{
			mAttackElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mAttackElapsed >= 1.0f)
			{
				mAttackElapsed = 0.0f;
				mCanAttack = true;
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState(VK_SPACE) != eKeyState::NONE)
			{
				COORD pos;
				pos.X = mPos.X + 10;
				pos.Y = mPos.Y + 5;

				Object* projectile = new Projectile(pos, { 15, 5 }, eSpriteType::PROJECTILE_RIGHT, false);
				Collider* col1 = new Collider({ 15, 15 }, { 0, 0 }, *projectile);
				projectile->AddCollider(col1);
				ObjectManager::GetInstance()->OnSpawn(projectile);
				ColliderManager::GetInstance()->OnRegister(col1);
				mCanAttack = false;
			}
		}
	}
}