#pragma once
#pragma once

#include "eObjectType.h"
#include "eSpriteType.h"
#include "hRectangle.h"
#include "Vector2.h"

namespace hockman
{
	class Collider;

	class Object
	{
	public:
		Object(hRectangle rectangle, eSpriteType spriteType, eObjectType objectType);
		virtual ~Object();

		virtual void Frame() = 0;
		virtual void Render();

		void AddCollider(Collider* collider);

		inline const hRectangle& GetRectangle() const;
		inline const eSpriteType& GetSpriteType() const;
		inline const eObjectType& GetObjectType() const;
		inline bool GetValid() const;
		inline Collider* GetCollider() const;

		inline void SetRectangle(const hRectangle& rect);

		inline void Move(float distanceX, float distanceY);

		void Rotate(float radian);

	protected:
		hRectangle mRectangle;
		eSpriteType mSpriteType;
		eObjectType mObjectType;
		Collider* mCollider;
		bool mIsVaild;
	};

	const hRectangle& Object::GetRectangle() const
	{
		return mRectangle;
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

	Collider* Object::GetCollider() const
	{
		return mCollider;
	}

	void Object::SetRectangle(const hRectangle& rect)
	{
		mRectangle = rect;
	}

	void Object::Move(float distanceX, float distanceY)
	{
		const Vector2& pos = mRectangle.GetTopLeft();
		mRectangle.SetPos(pos.GetX() + distanceX, pos.GetY() + distanceY);
	}
}
