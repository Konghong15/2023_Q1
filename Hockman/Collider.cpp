#include <cassert>

#include "Collider.h"
#include "RenderManager.h"

namespace hockman
{
	Collider::Collider(hRectangle offset, const Object& ownerObject)
		: mOffset(offset)
		, mOwnerObject(&ownerObject)
	{
		mCollisionObjects.reserve(RESERVE_SIZE);
		Init();
	}

	void Collider::CheckCollision(Collider& other)
	{
		hRectangle rect = GetWorldRectangle();
		hRectangle otherRect = other.GetWorldRectangle();

		if (hRectangle::IsCollision(rect, otherRect))
		{
			mCollisionObjects.push_back(&other);
			other.mCollisionObjects.push_back(this);
			mCollisionBitFlag |= static_cast<int>(other.GetOwnerObject().GetObjectType());
			other.mCollisionBitFlag |= static_cast<int>(GetOwnerObject().GetObjectType());
		}
	}

	void Collider::Init()
	{
		mCollisionObjects.clear();
		mCollisionBitFlag = 0;
		mPrevWorldRectangle = mWorldRectangle;
		const hRectangle& ownerRect = mOwnerObject->GetRectangle();
		mWorldRectangle = hRectangle(ownerRect.GetTopLeft() + mOffset.GetTopLeft(), ownerRect.GetBottomRight() - mOffset.GetBottomRight());
	}

	void Collider::Render()
	{
		if (mCollisionObjects.size() != 0)
		{
			RenderManager::GetInstance()->DrawRect(GetWorldRectangle(), RGB(255, 0, 0));
		}
		else
		{
			RenderManager::GetInstance()->DrawRect(GetWorldRectangle(), RGB(120, 0, 0));
		}
	}
};