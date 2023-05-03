#pragma once

#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "RenderManager.h"

namespace hockman
{
	Enemy::Enemy(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, float moveSpeed)
		: Object(pos, size, direction, spriteType, eObjectType::ENEMY)
		, mMoveSpeed(moveSpeed)
	{
	}

	void Enemy::Frame()
	{
		static bool isLeft = false;

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		const Scene& scene = SceneManager::GetInstance()->GetCurScene();


		if (mPos.GetX() + mSize.GetX() > scene.GetWidth())
		{
			isLeft = true;
		}
		else if (mPos.GetX() < 0)
		{
			isLeft = false;
		}

		if (isLeft)
		{
			mPos.SetX(mPos.GetX() - mMoveSpeed * DELTA_TIME);
		}
		else
		{
			mPos.SetX(mPos.GetX() + mMoveSpeed * DELTA_TIME);
		}
	}

	void Enemy::Render()
	{
		RenderManager::GetInstance()->DrawRect(mPos.GetX(), mPos.GetY(), mSize.GetX(), mSize.GetY(), RGB(0, 0, 255));
	}
}