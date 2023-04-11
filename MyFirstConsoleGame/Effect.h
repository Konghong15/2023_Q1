#pragma once

#include <Windows.h>
#include "Object.h"

namespace hongpireSurvivors
{
	class Effect : public Object
	{
	public:
		Effect(COORD pos, COORD size, eSpriteType* spriteTypes, size_t spriteLength, float spriteDuration, WORD color, bool isLeft = true);
		virtual ~Effect() override;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		eSpriteType* mSptieTypes;
		size_t mIndex;
		size_t mSpriteLength;
		WORD mColor;
		float mElapsed;
		float mSpriteDuration;
	};
}