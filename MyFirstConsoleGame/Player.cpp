#pragma once

#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Projectile.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "Helper.h"

namespace hongpireSurvivors
{
	Player::Player(COORD pos, COORD size, eSpriteType spriteType)
		: Object(pos, size, spriteType, eObjectType::PLAYER, true)
		, mCanMove(true)
		, mCanAttack(true)
		, mCanJump(true)
		, mElapsed(0.f)
		, mAttackElapsed(0.f)
		, mDropElapsed(0.f)
		, mJumpForce(0.f)
		, mAniElapsed(0.f)
	{
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		handleMove();
		handleJump();
		handleAttack();
		mPos.X = Helper::Clamp(0, Helper::MAP_WIDTH - mSize.X, mPos.X);
		mPos.Y = Helper::Clamp(0, Helper::MAP_HEIGHT - mSize.Y, mPos.Y);

		mAniElapsed -= DELTA_TIME;
		if (mAniElapsed < 0)
		{
			mAniElapsed = 0.f;
			mSpriteType = eSpriteType::PLAYER_IDLE;
		}
	}


	void Player::handleMove()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (!mCanMove)
		{
			mElapsed += DELTA_TIME;

			if (mElapsed >= 0.02f)
			{
				mElapsed -= 0.02f;
				mCanMove = true;
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
			{
				if (mCanJump)
				{
					mPos.X -= 2;
				}
				else
				{
					--mPos.X;
				}

				mCanMove = false;
				mIsLeft = true;
				
				mAniElapsed = 2.f;
				if (mSpriteType == eSpriteType::PLAYER_IDLE)
				{
					mSpriteType = eSpriteType::PLAYER_RUN;
				}
				else if (mSpriteType == eSpriteType::PLAYER_RUN)
				{
					mSpriteType = eSpriteType::PLAYER_IDLE;
				}
			}
			else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
			{
				if (mCanJump)
				{
					mPos.X += 2;
				}
				else
				{
					++mPos.X;
				}

				mCanMove = false;
				mIsLeft = false;
				
				mAniElapsed = 2.f;
				if (mSpriteType == eSpriteType::PLAYER_IDLE)
				{
					mSpriteType = eSpriteType::PLAYER_RUN;
				}
				else if (mSpriteType == eSpriteType::PLAYER_RUN)
				{
					mSpriteType = eSpriteType::PLAYER_IDLE;
				}
			}
		}
	}

	void Player::handleJump()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		if (!mCanJump)
		{
			mDropElapsed += DELTA_TIME;
		}

		if (InputManager::GetInstance()->GetKeyState(VK_UP) != eKeyState::NONE && mCanJump)
		{
			mJumpForce = 0.5f;
			mCanJump = false;
		}

		if (mDropElapsed >= 0.025f)
		{
			mDropElapsed -= 0.025f;

			if (mJumpForce > 0.25f)
			{
				mPos.Y -= 2;
				mAniElapsed = 2.f;
				mSpriteType = eSpriteType::PLAYER_JUMP;
			}
			else if (mJumpForce > 0.f)
			{
				mPos.Y -= 1;
			}
			else if (mJumpForce > -0.25f)
			{
				mPos.Y += 1;
			}
			else
			{
				mPos.Y += 2;
			}
		}

		mJumpForce -= DELTA_TIME * 1.5;

		if (mPos.Y + mSize.Y > 67)
		{
			mSpriteType = eSpriteType::PLAYER_IDLE;
			--mPos.Y;
			mCanJump = true;
			mJumpForce = 0.0f;
		}
	}

	void Player::handleAttack()
	{
		if (!mCanAttack)
		{
			mAttackElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mAttackElapsed >= 0.25f)
			{
				mAttackElapsed = 0.0f;
				mCanAttack = true;
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState(VK_SPACE) != eKeyState::NONE)
			{
				SHORT proj_y = mPos.Y + 3;
				Object* projectile = new Projectile({ mPos.X, proj_y }, { 15, 5 }, eSpriteType::PROJECTILE_RIGHT, mIsLeft);
				Collider* col1 = new Collider({ 15, 5 }, { 0, 0 }, *projectile);

				projectile->AddCollider(col1);
				ObjectManager::GetInstance()->OnSpawn(projectile);
				ColliderManager::GetInstance()->OnRegister(col1);

				mCanAttack = false;
				mAniElapsed = 0.1f;
				mSpriteType = eSpriteType::PLAYER_ATTACK;
			}
		}
	}
}