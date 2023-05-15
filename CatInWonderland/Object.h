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

		void Move(float distanceX, float distanceY);
		void Rotate(float radian, int originX, int originY);

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
}
