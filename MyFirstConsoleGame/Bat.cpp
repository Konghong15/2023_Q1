#pragma once

#include "Bat.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Helper.h"
#include "EnemyProjectile.h"

namespace hongpireSurvivors
{
	Bat::Bat(COORD pos, COORD size, eSpriteType spriteType, bool isLeft)
		: Monster(pos, size, spriteType, isLeft)
		, mCanAttack(false)
		, mAttackElapsed(0.f)
		, mDropElapsed(0.f)
		, mIsDrop(true)
	{
	}

	void Bat::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapsed += DELTA_TIME;
		mAttackElapsed += DELTA_TIME;
		mDropElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
		handleAttack();
		handleDirection();
	}

	void Bat::handleMove()
	{
		const Object& player = ObjectManager::GetInstance()->GetPlayer();
		COORD playerPos = player.GetPos();

		if (mDropElapsed >= 0.2f)
		{
			mDropElapsed -= 0.2f;
			mIsDrop = mIsDrop ^ true;
		}

		if (mElapsed >= 0.04f)
		{
			mElapsed -= 0.04f;

			if (mIsLeft)
			{
				mPos.X -= 2;

				if (mPos.X - playerPos.X < 100)
				{
					mCanAttack = true;
				}
			}
			else
			{
				mPos.X += 2;

				if (playerPos.X - mPos.X < 100)
				{
					mCanAttack = true;
				}
			}

			if (mIsDrop)
			{
				++mPos.Y;
			}
			else
			{
				--mPos.Y;
			}
		}
	}

	void Bat::handleAttack(void)
	{
		const Object& player = ObjectManager::GetInstance()->GetPlayer();
		COORD playerPos = player.GetPos();

		if (mAttackElapsed >= 2.f)
		{
			mAttackElapsed = 0.f;

			EnemyProjectile* proj = new EnemyProjectile(player.GetPos(), mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mIsLeft);
			Helper::Spawn(proj, mPos.X, mPos.Y, 4, 4);
		}
	}
}