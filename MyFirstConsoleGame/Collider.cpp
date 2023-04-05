#include "Collider.h"

namespace hongpireSurvivors
{
	Collider::Collider(COORD size, COORD offset, const Object& ownerObject)
		: mSize(size)
		, mOffset(offset)
		, mOwnerObject(&ownerObject)
		, mEnterBitFlag(0)
		, mPrevStayBitFlag(0)
		, mStayBitFlag(0)
		, mExitBitFlag(0)
	{
	}

	void Collider::CheckCollision(Collider& other)
	{

		COORD otherPos = other.GetWorldPosition();
		COORD curPos = GetWorldPosition();
		bool isCollision = false;


		if (otherPos.X > curPos.X)
		{
			isCollision = curPos.X + mSize.X > otherPos.X;
		}
		else
		{
			isCollision = otherPos.X + other.mSize.X > curPos.X;
		}

		if (isCollision)
		{
			if (otherPos.Y > curPos.Y)
			{
				isCollision = curPos.Y + mSize.Y > otherPos.Y;
			}
			else
			{
				isCollision = otherPos.Y + other.mSize.Y > curPos.Y;
			}
		}

		if (!isCollision)
		{
			return;
		}

		int bitMask = static_cast<int>(other.mOwnerObject->GetObjectType());

		if ((mEnterBitFlag & bitMask) != 0)
		{
			mEnterBitFlag != ~bitMask;
			mStayBitFlag |= bitMask;
		}
		else
		{
			mEnterBitFlag |= bitMask;
		}

		bitMask = static_cast<int>(this->mOwnerObject->GetObjectType());

		if ((other.mEnterBitFlag & bitMask) != 0)
		{
			other.mEnterBitFlag != ~bitMask;
			other.mStayBitFlag |= bitMask;
		}
		else
		{
			other.mEnterBitFlag |= bitMask;
		}
	}

	void Collider::CheckExitCollision()
	{
		mExitBitFlag = mPrevStayBitFlag ^ mStayBitFlag;

		mPrevStayBitFlag = mStayBitFlag;
		mStayBitFlag = 0;
	}
};