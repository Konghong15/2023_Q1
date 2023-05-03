#pragma once

#include <set>

#include "Object.h"
#include "Vector2.h"

namespace hockman
{
	class Collider
	{
	public:
		Collider(Vector2 size, Vector2 offset, const Object& ownerObject);
		~Collider() = default;

		void CheckCollision(Collider& other);
	
		void Render();
		void Release();

		inline const Vector2& GetSize() const;
		inline Vector2 GetWorldPosition() const;
		inline const Object& GetOwnerObject() const;
		inline const std::set<Collider*>& GetCollided() const;

	protected:
		Vector2 mSize;
		Vector2 mOffset;
		const Object* mOwnerObject;
		std::set<Collider*> mCollided;
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

	const std::set<Collider*>& Collider::GetCollided() const
	{
		return mCollided;
	}
}