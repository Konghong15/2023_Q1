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
		Collider(hRectangle rectangle, const Object& ownerObject);
		~Collider() = default;

		void CheckCollision(Collider& other);

		void Init();
		void Render();

		inline const hRectangle& GetRectangle() const;
		inline hRectangle GetWorldRectangle() const;
		inline const Object& GetOwnerObject() const;
		inline std::vector<Collider*>& GetCollisionObjects();

	protected:
		enum { RESERVE_SIZE = 128 };

		hRectangle mRectangle;
		const Object* mOwnerObject;
		std::vector<Collider*> mCollisionObjects;
	};

	const hRectangle& Collider::GetRectangle() const
	{
		return mRectangle;
	}

	hRectangle Collider::GetWorldRectangle() const
	{
		return hRectangle(mRectangle.GetPos() + mOwnerObject->GetRectangle().GetPos(), mRectangle.GetSize());
	}

	const Object& Collider::GetOwnerObject() const
	{
		return *mOwnerObject;
	}

	std::vector<Collider*>& Collider::GetCollisionObjects()
	{
		return mCollisionObjects;
	}
}