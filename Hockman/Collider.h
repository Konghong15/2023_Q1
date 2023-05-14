#pragma once

#include <vector>

#include "Object.h"
#include "hRectangle.h"
#include "eObjectType.h"

namespace hockman
{
	class Collider
	{
	public:
		Collider(hRectangle offset, const Object& ownerObject);
		~Collider() = default;

		void CheckCollision(Collider& other);

		void Init();
		void Render();

		inline const hRectangle& GetOffset() const;
		inline const hRectangle& GetWorldRectangle() const;
		inline const hRectangle& GetPrevWorldRectangle() const;

		inline const Object& GetOwnerObject() const;
		inline std::vector<Collider*>& GetCollisionObjects();
		inline int GetCollisionBitFlag() const;

	protected:
		enum { RESERVE_SIZE = 128 };

		hRectangle mOffset;
		hRectangle mWorldRectangle;
		hRectangle mPrevWorldRectangle;
		const Object* mOwnerObject;
		std::vector<Collider*> mCollisionObjects;
		int mCollisionBitFlag;
	};

	const hRectangle& Collider::GetOffset() const
	{
		return mOffset;
	}

	const hRectangle& Collider::GetPrevWorldRectangle() const
	{
		return mPrevWorldRectangle;
	}

	const hRectangle& Collider::GetWorldRectangle() const
	{
		return mWorldRectangle;
	}

	const Object& Collider::GetOwnerObject() const
	{
		return *mOwnerObject;
	}

	std::vector<Collider*>& Collider::GetCollisionObjects()
	{
		return mCollisionObjects;
	}

	int Collider::GetCollisionBitFlag() const
	{
		return mCollisionBitFlag;
	}
}