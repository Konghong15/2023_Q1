#pragma once

namespace hockman
{
	enum class eObjectType
	{
		PLAYER = 1,
		ENEMY = 2,
		PROJECTILE = 4,
		GROUND = 8,
		EFFECT = 16,
		BUTTON = 32
	};
}