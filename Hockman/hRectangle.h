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

		hRectangle(Vector2 position, Vector2 size);
		hRectangle(float x, float y, float w, float h);

		inline const Vector2& GetPos() const;
		inline const Vector2& GetSize() const;
		inline void SetPos(Vector2 pos);
		inline void SetPos(float x, float y);
		inline void Setsize(Vector2 size);
		inline void Setsize(float x, float y);

		Vector2 GetTopRight() const;
		Vector2 GetBottomLeft() const;
		Vector2 GetBottomRight() const;

		static bool IsCollision(const hRectangle& rect, const hRectangle& otherRect);
		static bool IsContained(const hRectangle& rect, const hRectangle& otherRect);

		static hRectangle GetIntersection(const hRectangle& rect, const hRectangle& otherRect);

	private:
		static hRectangle getUnion(const hRectangle& rect, const hRectangle& otherRect);

	private:
		Vector2 mPosition;
		Vector2 mSize;
	};

	const Vector2& hRectangle::GetPos() const
	{
		return mPosition;
	}

	const Vector2& hRectangle::GetSize() const
	{
		return mSize;
	}

	void hRectangle::SetPos(Vector2 pos)
	{
		mPosition = pos;
	}

	void hRectangle::SetPos(float x, float y)
	{
		mPosition.SetX(x);
		mPosition.SetY(y);
	}

	void hRectangle::Setsize(Vector2 size)
	{
		mSize = size;
	}

	void hRectangle::Setsize(float x, float y)
	{
		mSize.SetX(x);
		mSize.SetY(y);
	}
}