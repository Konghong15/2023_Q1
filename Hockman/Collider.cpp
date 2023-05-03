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
	}

	void Collider::CheckCollision(Collider& other)
	{
		Vector2 topLeft = GetWorldPosition();
		Vector2 bottomRight(topLeft.GetX() + mSize.GetX(), topLeft.GetY() + mSize.GetY());
		Vector2 otherTopLeft = other.GetWorldPosition();
		Vector2 otherBottomRight(otherTopLeft.GetX() + other.mSize.GetX(), otherTopLeft.GetY() + other.mSize.GetY());

		Vector2 unionTopLeft;
		unionTopLeft.SetX(topLeft.GetX() < otherTopLeft.GetX() ? topLeft.GetX() : otherTopLeft.GetX());
		unionTopLeft.SetY(topLeft.GetY() < otherTopLeft.GetY() ? topLeft.GetY() : otherTopLeft.GetY());
		Vector2 unionBottomRight;
		unionBottomRight.SetX(bottomRight.GetX() > otherBottomRight.GetX() ? bottomRight.GetX() : otherBottomRight.GetX());
		unionBottomRight.SetY(bottomRight.GetY() > otherBottomRight.GetY() ? bottomRight.GetY() : otherBottomRight.GetY());

		if (mSize.GetX() + other.mSize.GetX() < unionBottomRight.GetX() - unionTopLeft.GetX()
			|| mSize.GetY() + other.mSize.GetY() < unionBottomRight.GetY() - unionBottomRight.GetY())
		{
			mCollided.insert(&other);
			other.mCollided.insert(this);
		}
	}

	void Collider::Render()
	{
		if (mCollided.size() != 0)
		{
			RenderManager::GetInstance()->DrawRect(GetWorldPosition().GetX(), GetWorldPosition().GetY(), mSize.GetX(), mSize.GetY(), RGB(255, 0, 0));
		}
		else
		{
			RenderManager::GetInstance()->DrawRect(GetWorldPosition().GetX(), GetWorldPosition().GetY(), mSize.GetX(), mSize.GetY(), RGB(0, 0, 0));
		}
	}


	void Collider::Release()
	{
		mCollided.clear();
	}
};