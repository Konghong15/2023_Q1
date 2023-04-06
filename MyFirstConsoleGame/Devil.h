#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Devil : public Object
	{
	public:
		Devil(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Devil() = default;

		virtual void Frame() override;
	};
}