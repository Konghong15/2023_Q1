#pragma once

#include <cassert>

#include "Vector2.h"

namespace catInWonderland
{
	enum class eRectangleIndex
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Size
	};

	class hRectangle
	{
	public:
		hRectangle();
		~hRectangle() = default;
		hRectangle(const hRectangle&) = default;
		hRectangle& operator=(const hRectangle&) = default;

		hRectangle(Vector2 topLeft, Vector2 bottomRight);
		hRectangle(float x1, float y1, float x2, float y2);

		inline void Move(float x, float y);
		void Rotate(const Vector2& origin, float radian);

		inline void SetTopLeft(const Vector2& topLeft);
		inline void SetTopRight(const Vector2& bottomRight);
		inline void SetBottomLeft(const Vector2& bottomRight);
		inline void SetBottomRight(const Vector2& bottomRight);

		inline const Vector2& GetTopLeft() const;
		inline const Vector2& GetTopRight() const;
		inline const Vector2& GetBottomLeft() const;
		inline const Vector2& GetBottomRight() const;
		inline Vector2 GetCenter() const;
		inline Vector2 GetSize() const;
		inline float GetWidth() const;
		inline float GetHeight() const;

		static bool IsCollision(const hRectangle& rectangle, const hRectangle& otherRectangle);
		static bool IsContained(const hRectangle& rectangle, const hRectangle& otherRectangle);
		static hRectangle GetIntersection(const hRectangle& rectangle, const hRectangle& otherRectangle);
		static hRectangle GetBoundingRectangle(const hRectangle& rectangle);

	private:
		inline Vector2& getVertex(eRectangleIndex rectangleIndex);
		inline const Vector2& getVertex(eRectangleIndex rectangleIndex) const;

	private:
		Vector2 mVertices[static_cast<size_t>(eRectangleIndex::Size)];
	};

	void hRectangle::Move(float x, float y)
	{
		for (size_t i = 0; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
		{
			mVertices[i].Move(x, y);
		}
	}

	void hRectangle::SetTopLeft(const Vector2& topLeft)
	{
		getVertex(eRectangleIndex::TopLeft) = topLeft;
	}

	void hRectangle::SetTopRight(const Vector2& topRight)
	{
		getVertex(eRectangleIndex::TopRight) = topRight;
	}

	void hRectangle::SetBottomLeft(const Vector2& bottomLeft)
	{
		getVertex(eRectangleIndex::BottomLeft) = bottomLeft;
	}

	void hRectangle::SetBottomRight(const Vector2& bottomRight)
	{
		getVertex(eRectangleIndex::BottomRight) = bottomRight;
	}

	const Vector2& hRectangle::GetTopLeft() const
	{
		return getVertex(eRectangleIndex::TopLeft);
	}

	const Vector2& hRectangle::GetTopRight() const
	{
		return getVertex(eRectangleIndex::TopRight);
	}

	const Vector2& hRectangle::GetBottomLeft() const
	{
		return getVertex(eRectangleIndex::BottomLeft);
	}

	const Vector2& hRectangle::GetBottomRight() const
	{
		return getVertex(eRectangleIndex::BottomRight);
	}

	Vector2 hRectangle::GetCenter() const
	{
		const Vector2& topLeft = getVertex(eRectangleIndex::TopLeft);
		const Vector2& bottomRight = getVertex(eRectangleIndex::BottomRight);

		return Vector2((topLeft.GetX() + bottomRight.GetX()) * 0.5f, (topLeft.GetY() + bottomRight.GetY()) * 0.5f);
	}

	Vector2 hRectangle::GetSize() const
	{
		return Vector2(GetWidth(), GetHeight());
	}

	float hRectangle::GetWidth() const
	{
		return Vector2::GetDistance(getVertex(eRectangleIndex::TopLeft), getVertex(eRectangleIndex::TopRight));
	}

	float hRectangle::GetHeight() const
	{
		return Vector2::GetDistance(getVertex(eRectangleIndex::TopLeft), getVertex(eRectangleIndex::BottomLeft));
	}

	Vector2& hRectangle::getVertex(eRectangleIndex rectangleIndex)
	{
		assert(rectangleIndex != eRectangleIndex::Size);

		return mVertices[static_cast<size_t>(rectangleIndex)];
	}

	inline const Vector2& hRectangle::getVertex(eRectangleIndex rectangleIndex) const
	{
		assert(rectangleIndex != eRectangleIndex::Size);

		return mVertices[static_cast<size_t>(rectangleIndex)];
	}
}