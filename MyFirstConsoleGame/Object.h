#pragma once

#include <Windows.h>

#include "eSpriteType.h"
#include "eObjectType.h"

namespace hongpireSurvivors
{
	class Collider;
	class Scene;

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
		inline bool GetIsLeft() const;

	protected:
		enum { MONSTER_SPEED_LOW = 1 };
		enum { MONSTER_SPEED_MIDDLE = 2 };
		enum { MONSTER_SPEED_HIGH = 3 };
		enum { MONSTER_SPEED_VERY_HIGH = 5 };
		enum { PROJECTILE_SPEED_SLOW = 3 };
		enum { PROJECTILE_SPEED_MIDDLE = 5 };
		enum { PROJECTILE_SPEED_HIGH = 7 };
		enum { PLAYER_SPEED = 3 };
		enum { PLAYER_SPEED_ON_JUMP = 2 };

		static const float ONE_FRAME_TIME;

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

	bool Object::GetIsLeft() const
	{
		return mIsLeft;
	}
}