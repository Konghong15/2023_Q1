#pragma once

#include "Vector2.h"

namespace hockman
{
	class hRectangle
	{
	public:
		hRectangle();
		~hRectangle() = default;
		hRectangle(const hRectangle&) = default;
		hRectangle& operator=(const hRectangle&) = default;

		hRectangle(Vector2 topLeft, Vector2 bottomRight);
		hRectangle(float x1, float y1, float x2, float y2);

		inline void SetTopLeft(const Vector2& topLeft);
		inline void SetBottomRight(const Vector2& bottomRight);
		inline void SetPos(const Vector2& pos);
		inline void SetPos(float x, float y);
		inline void Setsize(float x, float y);

		inline Vector2 GetTopLeft() const;
		inline Vector2 GetTopRight() const;
		inline Vector2 GetBottomLeft() const;
		inline Vector2 GetBottomRight() const;
		inline Vector2 GetCenter() const;
		inline Vector2 GetSize() const;
		inline float GetWidth() const;
		inline float GetHeight() const;

		static bool IsCollision(const hRectangle& rect, const hRectangle& otherRect);
		static bool IsContained(const hRectangle& rect, const hRectangle& otherRect);
		static hRectangle GetIntersection(const hRectangle& rect, const hRectangle& otherRect);

	private:
		static hRectangle getUnion(const hRectangle& rect, const hRectangle& otherRect);

	private:
		Vector2 mTopLeft;
		Vector2 mBottomRight;
	};

	void hRectangle::SetTopLeft(const Vector2& topLeft)
	{
		mTopLeft = topLeft;
	}

	void hRectangle::SetBottomRight(const Vector2& bottomRight)
	{
		mBottomRight = bottomRight;
	}

	void hRectangle::SetPos(const Vector2& pos)
	{
		mBottomRight.SetX(pos.GetX() + GetWidth());
		mBottomRight.SetY(pos.GetY() + GetHeight());
		mTopLeft.SetX(pos.GetX());
		mTopLeft.SetY(pos.GetY());
	}

	void hRectangle::SetPos(float x, float y)
	{
		mBottomRight.SetX(x + GetWidth());
		mBottomRight.SetY(y + GetHeight());
		mTopLeft.SetX(x);
		mTopLeft.SetY(y);
	}

	void hRectangle::Setsize(float x, float y)
	{
		mBottomRight.SetX(mTopLeft.GetX() + x);
		mBottomRight.SetY(mTopLeft.GetX() + y);
	}

	Vector2 hRectangle::GetTopLeft() const
	{
		return mTopLeft;
	}

	Vector2 hRectangle::GetTopRight() const
	{
		return Vector2(mBottomRight.GetX(), mTopLeft.GetY());
	}

	Vector2 hRectangle::GetBottomLeft() const
	{
		return Vector2(mTopLeft.GetX(), mBottomRight.GetY());
	}

	Vector2 hRectangle::GetBottomRight() const
	{
		return mBottomRight;
	}

	Vector2 hRectangle::GetCenter() const
	{
		return Vector2((mTopLeft.GetX() + mBottomRight.GetX()) * 0.5f, (mTopLeft.GetY() + mBottomRight.GetY()) * 0.5f);
	}

	Vector2 hRectangle::GetSize() const
	{
		return Vector2(GetWidth(), GetHeight());
	}

	float hRectangle::GetWidth() const
	{
		return mBottomRight.GetX() - mTopLeft.GetX();
	}

	float hRectangle::GetHeight() const
	{
		return mBottomRight.GetY() - mTopLeft.GetY();
	}
}