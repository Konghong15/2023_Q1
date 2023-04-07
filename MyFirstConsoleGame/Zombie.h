#pragma once

#include "Monster.h"
#include "eSpriteType.h"

namespace hongpireSurvivors
{
	class Zombie : public Monster
	{
	public:
		Zombie(COORD pos, COORD size, eSpriteType spriteType, bool isLeft = true);
		virtual ~Zombie() = default;

	protected:
		virtual void handleMove() override;
	};
}