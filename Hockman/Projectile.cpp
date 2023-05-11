#include "Projectile.h"
#include "TimeManager.h"

namespace hockman
{
	Projectile::Projectile(hRectangle rectangle, eSpriteType spriteType, Vector2 direction, float velocity, float accel, float lifeTime)
		: Object(rectangle, eSpriteType::Projectile, eObjectType::PROJECTILE)
		, mDirection(direction.GetNormalized())
		, mVelocity(velocity)
		, mAccel(accel)
		, mLifeTime(lifeTime)
	{

	}

	void Projectile::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

		mVelocity += mAccel * DELTA_TIME;

		float distanceX = mDirection.GetX() * mVelocity * DELTA_TIME;
		float distanceY = mDirection.GetY() * mVelocity * DELTA_TIME;
		Move(distanceX, distanceY);
	}

	void Projectile::Render()
	{

	}
}