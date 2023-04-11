#pragma once

#include <cassert>

#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Projectile.h"
#include "Effect.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "RenderManager.h"
#include "Scene.h"
#include "Helper.h"
#include "SoundManager.h"

namespace hongpireSurvivors
{
	Player::Player(COORD pos, COORD size, eSpriteType spriteType)
		: Object(pos, size, spriteType, eObjectType::PLAYER, true)
		, mCanAttack(true)
		, mCanJump(true)
		, mCanHit(true)
		, mShild(true)
		, mElapsed(0.f)
		, mAttackElapsed(0.f)
		, mDropElapsed(0.f)
		, mJumpForce(0.f)
		, mAniElapsed(0.f)
		, mHitElapsed(1.f)
	{
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		handleMove();
		handleJump();
		handleAttack();
		handleCollision();
		mPos.X = Helper::Clamp(Scene::mScene->GetCamara().X, Scene::mScene->GetCamara().X + 370, mPos.X);
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
		if (mElapsed < ONE_FRAME_TIME)
		{
			return;
		}
		mElapsed -= ONE_FRAME_TIME;

		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) != eKeyState::NONE)
		{
			if (mCanJump)
			{
				mPos.X -= PLAYER_SPEED;
			}
			else
			{
				mPos.X -= PLAYER_SPEED_ON_JUMP;
			}

			mIsLeft = true;

			mAniElapsed = 2.f;
			if (mSpriteType == eSpriteType::PLAYER_IDLE)
			{
				mSpriteType = eSpriteType::PLAYER_RUN_0;
			}
			else if (mSpriteType == eSpriteType::PLAYER_RUN_0)
			{
				mSpriteType = eSpriteType::PLAYER_IDLE;
			}
		}
		else if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) != eKeyState::NONE)
		{
			if (mCanJump)
			{
				mPos.X += PLAYER_SPEED;
			}
			else
			{
				mPos.X += PLAYER_SPEED_ON_JUMP;
			}

			mIsLeft = false;

			mAniElapsed = 2.f;
			if (mSpriteType == eSpriteType::PLAYER_IDLE)
			{
				mSpriteType = eSpriteType::PLAYER_RUN_0;
			}
			else if (mSpriteType == eSpriteType::PLAYER_RUN_0)
			{
				mSpriteType = eSpriteType::PLAYER_IDLE;
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
			SoundManager::GetInstance()->Play(eSound::PLAYER_JUMP);
			mJumpForce = 0.5f;
			mCanJump = false;
		}

		if (mDropElapsed >= ONE_FRAME_TIME)
		{
			mDropElapsed -= 0.03f;

			if (mJumpForce > 0.3f)
			{
				mPos.Y -= 3;
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
				mPos.Y += 3;
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

			if (mAttackElapsed >= ONE_FRAME_TIME * 7)
			{
				mAttackElapsed = 0.0f;
				mCanAttack = true;
			}
		}
		else
		{
			if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == eKeyState::PUSH)
			{
				SoundManager::GetInstance()->Play(eSound::PLAYER_THROW);

				SHORT proj_y = mPos.Y + 3;
				Object* projectile = new Projectile({ mPos.X, proj_y }, { 15, 5 }, eSpriteType::PROJECTIE, mIsLeft);
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

	void Player::handleCollision()
	{
		assert(mCollider != nullptr);
		int flag = mCollider->GetEnterBitFlag();
		int monsterFlag = static_cast<int>(eObjectType::ENEMY);

		if (!mCanHit)
		{
			mHitElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mHitElapsed >= 3.0f)
			{
				mHitElapsed = 0;
				mCanHit = true;
			}

			return;
		}

		if ((flag & monsterFlag) != 0 && mCanHit)
		{
			if (mShild)
			{
				SoundManager::GetInstance()->Play(eSound::PLAYER_HIT);
				eSpriteType spriteTypes[2] = { eSpriteType::PLAYER_WOUNDED_0, eSpriteType::PLAYER_WOUNDED_1 };
				Effect* effect = new Effect({ (SHORT)(mPos.X - 3), (SHORT)(mPos.Y - 3) }, { (SHORT)20, (SHORT)15 }, spriteTypes, 2, 0.25f, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::WHITE), mIsLeft);
				ObjectManager::GetInstance()->OnSpawn(effect);
				mShild = false;
			}
			else
			{
				SoundManager::GetInstance()->Play(eSound::PLAYER_DEATH);
				eSpriteType spriteTypes[4] = { eSpriteType::PLAYER_DEAD_0, eSpriteType::PLAYER_DEAD_1, eSpriteType::PLAYER_DEAD_2, eSpriteType::PLAYER_DEAD_3 };
				Effect* effect = new Effect({ (SHORT)(mPos.X), (SHORT)(67 - 17) }, { (SHORT)20, (SHORT)17 }, spriteTypes, 4, 0.5f, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE), mIsLeft);
				ObjectManager::GetInstance()->OnSpawn(effect);
				//mIsVaild = false;
			}

			mCanHit = false;
		}
	}

	void Player::Render()
	{
		int x = mPos.X - Scene::mScene->GetCamara().X;

		if (x >= 0 && x + mSize.X < 400)
		{
			if (mShild)
			{
				RenderManager::GetInstance()->Draw(x, mPos.Y, mSpriteType, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_WHITE), mIsLeft);
			}
			else
			{
				RenderManager::GetInstance()->Draw(x, mPos.Y, mSpriteType, RenderManager::GetInstance()->GetColor(eConsoleColor::BLACK, eConsoleColor::DEEP_YELLOW), mIsLeft);
			}
		}
	}
}