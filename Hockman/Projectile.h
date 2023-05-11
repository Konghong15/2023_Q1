#pragma once

#include "Object.h"

namespace hockman
{
	class Projectile final : public Object
	{
	public:
		Projectile(hRectangle rectangle, eSpriteType spriteType, Vector2 direction, float velocity, float accel, float lifeTime);
		~Projectile() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		Vector2 mDirection;
		float mVelocity;
		float mAccel;
		float mLifeTime;
	};
}