#pragma once

#include <vector>

#include "Object.h"
#include "Vector2.h"
#include "eObjectType.h"

namespace hockman
{
	class Collider
	{
	public:
		Collider(Vector2 size, Vector2 offset, const Object& ownerObject);
		~Collider() = default;

		void CheckCollision(Collider& other);

		void Init();
		void Render();

		inline const Vector2& GetSize() const;
		inline Vector2 GetWorldPosition() const;
		inline const Object& GetOwnerObject() const;
		inline std::vector<Collider*>& GetCollisionObjects();

	protected:
		enum { RESERVE_SIZE = 128 };

		Vector2 mSize;
		Vector2 mOffset;
		const Object* mOwnerObject;
		std::vector<Collider*> mCollisionObjects;
	};

	const Vector2& Collider::GetSize() const
	{
		return mSize;
	}

	Vector2 Collider::GetWorldPosition() const
	{
		Vector2 worldPos = mOwnerObject->GetPos();

		return Vector2(worldPos.GetX() + mOffset.GetX(), worldPos.GetY() + mOffset.GetY());
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