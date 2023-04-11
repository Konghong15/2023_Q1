#pragma once

#include <Windows.h>

#include "Object.h"

namespace hongpireSurvivors
{
	class Collider
	{
	public:
		Collider(COORD size, COORD offset, const Object& ownerObject);
		~Collider() = default;

		void CheckCollision(Collider& other);
		void CheckExitCollision();

		inline const COORD& GetSize() const;
		inline COORD GetWorldPosition() const;
		inline const Object& GetOwnerObject() const;

		inline int GetEnterBitFlag() const;
		inline int GetStayBitFlag() const;
		inline int GetExitBitFlag() const;

		inline void InitEnter();

	protected:
		COORD mSize;
		COORD mOffset;
		const Object* mOwnerObject;

		int mEnterBitFlag;
		int mPrevStayBitFlag;
		int mStayBitFlag;
		int mExitBitFlag;
	};

	const COORD& Collider::GetSize() const
	{
		return mSize;
	}

	COORD Collider::GetWorldPosition() const
	{
		COORD worldPos = mOwnerObject->GetPos();
		worldPos.X += mOffset.X;
		worldPos.Y += mOffset.Y;

		return worldPos;
	}

	const Object& Collider::GetOwnerObject() const
	{
		return *mOwnerObject;
	}

	int Collider::GetEnterBitFlag() const
	{
		return mEnterBitFlag;
	}

	int Collider::GetStayBitFlag() const
	{
		return mPrevStayBitFlag;
	}

	int Collider::GetExitBitFlag() const
	{
		return mExitBitFlag;
	}

	void Collider::InitEnter()
	{
		mEnterBitFlag = 0;
	}
}