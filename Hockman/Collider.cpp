#include <cassert>

#include "Collider.h"
#include "RenderManager.h"

namespace hockman
{

	Collider::Collider(hRectangle rectangle, const Object& ownerObject)
		: mRectangle(rectangle)
		, mOwnerObject(&ownerObject)
	{
		mCollisionObjects.reserve(RESERVE_SIZE);
	}

	void Collider::CheckCollision(Collider& other)
	{
		hRectangle rect = GetWorldRectangle();
		hRectangle otherRect = other.GetWorldRectangle();

		if (hRectangle::IsCollision(rect, otherRect))
		{
			mCollisionObjects.push_back(&other);
			other.mCollisionObjects.push_back(this);
		}
	}

	void Collider::Init()
	{
		mCollisionObjects.clear();
	}

	void Collider::Render()
	{
		if (mCollisionObjects.size() != 0)
		{
			RenderManager::GetInstance()->DrawRect(GetWorldRectangle(), RGB(255, 0, 0));
		}
		else
		{
			RenderManager::GetInstance()->DrawRect(GetWorldRectangle(), RGB(0, 0, 0));
		}
	}
};