#include "Bat.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Helper.h"
#include "EnemyProjectile.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	Bat::Bat(COORD pos, COORD size, eSpriteType spriteType, int minX, int maxX, bool isLeft, int hp)
		: Monster(pos, size, spriteType, minX, maxX, hp, isLeft)
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
		const Object& player = Scene::mScene->GetPlayer();
		COORD playerPos = player.GetPos();

		if (mDropElapsed >= ONE_FRAME_TIME)
		{
			mDropElapsed -= ONE_FRAME_TIME;
			mIsDrop = mIsDrop ^ true;
		}

		if (mElapsed >= ONE_FRAME_TIME)
		{
			mElapsed -= ONE_FRAME_TIME;

			if (mIsLeft)
			{
				mPos.X -= MONSTER_SPEED_MIDDLE;
			}
			else
			{
				mPos.X += MONSTER_SPEED_MIDDLE;
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
		const Object& player = Scene::mScene->GetPlayer();
		COORD playerPos = player.GetPos();

		if (abs(mPos.X - playerPos.X) < 100)
		{
			mCanAttack = true;
		}

		if (!mCanAttack)
		{
			return;
		}

		if (mAttackElapsed >= ONE_FRAME_TIME * 60)
		{
			mAttackElapsed = 0.f;

			EnemyProjectile* proj = new EnemyProjectile(player.GetPos(), mPos, { 4, 4 }, eSpriteType::ENEMY_1_PROJECTILE, mMinX, mMaxX, mIsLeft);
			Helper::Spawn(proj, 4, 4);
			mCanAttack = false;
		}
	}
}