#pragma once

#include <Windows.h>

#include "eSpriteType.h"
#include "eObjectType.h"

namespace hongpireSurvivors
{
	class Collider;

	class Object
	{
	public:
		Object(COORD pos, COORD size, eSpriteType spriteType, eObjectType objectType, bool isLeft = true);
		virtual ~Object();

		virtual void Frame() = 0;
		virtual void Render();

		void AddCollider(Collider* collider);

		inline const COORD& GetPos() const;
		inline const COORD& GetSize() const;
		inline eSpriteType GetSpriteType() const;
		inline eObjectType GetObjectType() const;
		inline bool GetValid() const;

	protected:
		COORD mPos;
		COORD mSize;
		eSpriteType mSpriteType;
		eObjectType mObjectType;
		Collider* mCollider;
		bool mIsVaild;
		bool mIsLeft;
	};

	const COORD& Object::GetPos() const
	{
		return mPos;
	}

	const COORD& Object::GetSize() const
	{
		return mSize;
	}

	eSpriteType Object::GetSpriteType() const
	{
		return mSpriteType;
	}

	eObjectType Object::GetObjectType() const
	{
		return mObjectType;
	}

	bool Object::GetValid() const
	{
		return mIsVaild;
	}
}