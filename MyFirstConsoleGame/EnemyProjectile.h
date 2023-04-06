#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class EnemyProjectile : public Object
	{
	public:
		EnemyProjectile(COORD pos, COORD size, eSpriteType spriteType, bool isLeft);
		virtual ~EnemyProjectile() = default;

		virtual void Frame() override;

	private:
		float mElapsed;
		bool mCanMove;
	};
}