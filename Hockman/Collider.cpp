#include <cassert>

#include "Collider.h"
#include "RenderManager.h"

namespace hockman
{
	Collider::Collider(Vector2 size, Vector2 offset, const Object& ownerObject)
		: mSize(size)
		, mOffset(offset)
		, mOwnerObject(&ownerObject)
	{
		mCollisionObjects.reserve(RESERVE_SIZE);
	}

	void Collider::CheckCollision(Collider& other)
	{
		Vector2 topLeft = GetWorldPosition();
		Vector2 bottomRight(topLeft.GetX() + mSize.GetX(), topLeft.GetY() + mSize.GetY());
		Vector2 otherTopLeft = other.GetWorldPosition();
		Vector2 otherBottomRight(otherTopLeft.GetX() + other.mSize.GetX(), otherTopLeft.GetY() + other.mSize.GetY());

		if (bottomRight.GetX() < otherTopLeft.GetX() || otherBottomRight.GetX() < topLeft.GetX()
			|| topLeft.GetY() > otherBottomRight.GetY() || otherTopLeft.GetY() > bottomRight.GetY()) // 스크린 좌표 기준
		{
			return;
		}

		mCollisionObjects.push_back(&other);
		other.mCollisionObjects.push_back(this);
	}

	void Collider::Init()
	{
		mCollisionObjects.clear();
	}

	void Collider::Render()
	{
		if (mCollisionObjects.size() != 0)
		{
			RenderManager::GetInstance()->DrawRect(GetWorldPosition().GetX(), GetWorldPosition().GetY(), mSize.GetX(), mSize.GetY(), RGB(255, 0, 0));
		}
		else
		{
			RenderManager::GetInstance()->DrawRect(GetWorldPosition().GetX(), GetWorldPosition().GetY(), mSize.GetX(), mSize.GetY(), RGB(0, 0, 0));
		}
	}
};