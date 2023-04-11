#include "KingOrge.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Helper.h"
#include "EnemyProjectile.h"
#include "Bat.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	KingOrge::KingOrge(COORD pos, COORD size, int minX, int maxX, bool isLeft)
		: Monster(pos, size, eSpriteType::BOSS_2_IDLE, minX, maxX, 15, isLeft)
		, mAttackElapsed(0.f)
		, mSpawnElaapsed(0.f)
		, mAniElapsed(0.f)
	{
	}

	void KingOrge::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mElapsed += DELTA_TIME;
		mAttackElapsed += DELTA_TIME;
		mSpawnElaapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleAttack();
		handleAnimation();
		handleMove();
		handleDirection();
	}

	void KingOrge::handleMove()
	{
		const float FRAME_TIME = ONE_FRAME_TIME * 30;

		if (mElapsed >= FRAME_TIME)
		{
			mElapsed -= FRAME_TIME;

			mPos.X += mIsLeft ? -MONSTER_SPEED_LOW : MONSTER_SPEED_LOW;
		}
	}

	void KingOrge::handleAttack()
	{
		const float ATTACK_FRAME_TIME = ONE_FRAME_TIME * 30;
		const float SPAWN_FRAME_TIME = ONE_FRAME_TIME * 120;

		COORD playerPos = Scene::mScene->GetPlayer().GetPos();
		mIsLeft = playerPos.X > mPos.X ? false : true;

		if (mAttackElapsed >= ATTACK_FRAME_TIME)
		{
			mAttackElapsed -= ATTACK_FRAME_TIME;
			mAniElapsed = ONE_FRAME_TIME * 15;
			mSpriteType = eSpriteType::BOSS_2_ATTACK;

			Object* obj = new EnemyProjectile(playerPos, { mPos.X, (SHORT)(mPos.Y + 2) }, { 15, 8 }, eSpriteType::BOSS_2_PROJECTILE, mMinX, mMaxX, mIsLeft);
			Helper::Spawn(obj, 15, 8);
		}

		if (mSpawnElaapsed >= SPAWN_FRAME_TIME)
		{
			mSpawnElaapsed -= SPAWN_FRAME_TIME;

			SHORT x = Helper::Clamp(0, Helper::MAP_WIDTH - 20, mPos.X + 10);
			Object* obj = new Bat({ x, mPos.Y }, { 20, 8 }, eSpriteType::ENEMY_2, mMinX, mMaxX, mIsLeft, 1);
			Helper::Spawn(obj, 20, 8);
		}
	}

	void KingOrge::handleAnimation()
	{
		if (mSpriteType == eSpriteType::BOSS_2_ATTACK)
		{
			mAniElapsed -= TimeManager::GetInstance()->GetDeltaTime();
		}

		if (mAniElapsed <= 0.f)
		{
			mSpriteType = eSpriteType::BOSS_2_IDLE;
		}
	}
}