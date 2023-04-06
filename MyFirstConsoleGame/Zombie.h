#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Zombie : public Object
	{
	public:
		Zombie(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Zombie() = default;

		virtual void Frame() override;
	};
}