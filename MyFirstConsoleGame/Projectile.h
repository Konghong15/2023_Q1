#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Projectile : public Object
	{
	public:
		Projectile(COORD pos, COORD size, eSpriteType spriteType, bool isLeft);
		virtual ~Projectile() = default;

		virtual void Frame() override;

		void handleMove();
		void handleCollision();

	private:
		float mElapsed;
		bool mCanMove;
	};
}