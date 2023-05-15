#pragma once

#include "hRectangle.h"
#include "Vector2.h"

namespace catInWonderland
{
	class Collider;

	class Object
	{
	public:
		Object(hRectangle rectangle, size_t indexX, size_t indexY);
		virtual ~Object();

		virtual void Frame() = 0;
		virtual void Render();

		inline const hRectangle& GetRectangle() const;
		inline bool GetValid() const;
		inline size_t GetIndexX() const;
		inline size_t GetIndexY() const;

		void Move(float distanceX, float distanceY);
		void Rotate(int originX, int originY, float radian);
		void RotateIndex(bool bLeft);

	private:
		void adjustRectangle();

	protected:
		hRectangle mRectangle;
		size_t mIndexX;
		size_t mIndexY;
		bool mIsVaild;
	};

	const hRectangle& Object::GetRectangle() const
	{
		return mRectangle;
	}

	bool Object::GetValid() const
	{
		return mIsVaild;
	}

	size_t Object::GetIndexX() const
	{
		return mIndexX;
	}

	size_t Object::GetIndexY() const
	{
		return mIndexY;
	}
}
