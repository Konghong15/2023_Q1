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
		virtual void Render() override;

	private:
		void handleMove();
		void handleCollision();

	private:
		const COORD START_POS;
		float mElapsed;
	};
}