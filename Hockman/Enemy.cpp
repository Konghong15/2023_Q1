#pragma once

#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "RenderManager.h"

namespace hockman
{
	Enemy::Enemy(hRectangle rectangle, eSpriteType spriteType, float moveSpeed)
		: Object(rectangle, spriteType, eObjectType::ENEMY)
		, mMoveSpeed(moveSpeed)
	{
	}

	void Enemy::Frame()
	{
		static bool isLeft = false;

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		const Scene& scene = SceneManager::GetInstance()->GetCurScene();

		const Vector2& pos = mRectangle.GetPos();
		const Vector2& size = mRectangle.GetSize();

		if (pos.GetX() + size.GetX() > scene.GetWidth())
		{
			isLeft = true;
		}
		else if (pos.GetX() < 0)
		{
			isLeft = false;
		}

		float moveAmount = 0.f;

		if (isLeft)
		{
			moveAmount = -mMoveSpeed * DELTA_TIME;
		}
		else
		{
			moveAmount = mMoveSpeed * DELTA_TIME;
		}

		Move(moveAmount, 0);
	}

	void Enemy::Render()
	{
		RenderManager::GetInstance()->DrawRect(mRectangle, RGB(0, 0, 255));
	}
}