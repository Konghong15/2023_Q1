#pragma once

#include <Windows.h>

#include "eSpriteType.h"

namespace hongpireSurvivors
{
	class Object
	{
	public:
		Object(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Object() = default;

		inline COORD& GetPos();
		inline COORD& GetSize();
		inline eSpriteType GetSpriteType();

		virtual void Frame() = 0;
		virtual void Render();

	protected:
		COORD mPos;
		COORD mSize;
		eSpriteType mSpriteType;
	};

	COORD& Object::GetPos()
	{
		return mPos;
	}

	COORD& Object::GetSize()
	{
		return mSize;
	}

	eSpriteType Object::GetSpriteType()
	{
		return mSpriteType;
	}
}