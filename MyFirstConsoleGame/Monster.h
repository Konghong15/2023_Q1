#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Monster : public Object
	{
	public:
		Monster(COORD pos, COORD size, eSpriteType spriteType, bool isLeft = true);
		virtual ~Monster() = default;

		virtual void Frame() override;

	protected:
		virtual void handleCollision();
		virtual void handleDirection();
		virtual void handleMove() = 0;

	protected:
		float mElapsed;
		bool mCanMove;
	};
}