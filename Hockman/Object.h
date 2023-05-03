#pragma once

#include "eObjectType.h"
#include "eSpriteType.h"
#include "Vector2.h"

namespace hockman
{
	class Collider;

	class Object
	{
	public:
		Object(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, eObjectType objectType);
		virtual ~Object();

		virtual void Frame() = 0;
		virtual void Render();

		void AddCollider(Collider* collider);

		inline const Vector2& GetPos() const;
		inline const Vector2& GetSize() const;
		inline const Vector2& GetDirection() const;
		inline const eSpriteType& GetSpriteType() const;
		inline const eObjectType& GetObjectType() const;
		inline bool GetValid() const;

	protected:
		Vector2 mPos;
		Vector2 mSize;
		Vector2 mDirection;
		eSpriteType mSpriteType;
		eObjectType mObjectType;
		Collider* mCollider;
		bool mIsVaild;
	};

	const Vector2& Object::GetPos() const
	{
		return mPos;
	}

	const Vector2& Object::GetSize() const
	{
		return mSize;
	}

	const Vector2& Object::GetDirection() const
	{
		return mDirection;
	}

	const eSpriteType& Object::GetSpriteType() const
	{
		return mSpriteType;
	}

	const eObjectType& Object::GetObjectType() const
	{
		return mObjectType;
	}

	bool Object::GetValid() const
	{
		return mIsVaild;
	}
}
