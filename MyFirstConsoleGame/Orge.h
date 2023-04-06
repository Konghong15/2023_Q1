#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Orge : public Object
	{
	public:
		Orge(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Orge() = default;

		virtual void Frame() override;
	};
}