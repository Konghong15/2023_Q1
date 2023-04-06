#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Bat : public Object
	{
	public:
		Bat(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Bat() = default;

		virtual void Frame() override;
	};
}