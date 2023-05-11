#include <memory.h>

#include "hRectangle.h"

namespace hockman
{
	hRectangle::hRectangle()
		: hRectangle(0.f, 0.f, 0.f, 0.f)
	{
	}

	hRectangle::hRectangle(Vector2 position, Vector2 size)
		: mPosition(position)
		, mSize(size)
	{
	}

	hRectangle::hRectangle(float x, float y, float w, float h)
		: mPosition(x, y)
		, mSize(w, h)
	{
	}

	Vector2 hRectangle::GetTopRight() const
	{
		return Vector2(mPosition.GetX() + mSize.GetX(), mPosition.GetY());
	}

	Vector2 hRectangle::GetBottomLeft() const
	{
		return Vector2(mPosition.GetX(), mPosition.GetY() + mSize.GetY());
	}

	Vector2 hRectangle::GetBottomRight() const
	{
		return Vector2(mPosition.GetX() + mSize.GetX(), mPosition.GetY() + mSize.GetY());
	}

	bool hRectangle::IsCollision(const hRectangle& rect, const hRectangle& otherRect)
	{
		hRectangle unionRect(getUnion(rect, otherRect));
		Vector2 topLeft(rect.GetPos());
		Vector2 bottomRight(rect.GetBottomRight());
		Vector2 otherTopLeft = otherRect.GetPos();
		Vector2 otherBottomRight(otherRect.GetBottomRight());

		return bottomRight.GetX() >= otherTopLeft.GetX() && otherBottomRight.GetX() >= topLeft.GetX()
			&& topLeft.GetY() <= otherBottomRight.GetY() && otherTopLeft.GetY() <= bottomRight.GetY();
	}

	bool hRectangle::IsContained(const hRectangle& rect, const hRectangle& otherRect)
	{
		hRectangle unionRect = getUnion(rect, otherRect);

		return unionRect.mSize == rect.mSize;
	}

	hRectangle hRectangle::GetIntersection(const hRectangle& rect, const hRectangle& otherRect)
	{
		if (!IsCollision(rect, otherRect))
		{
			return hRectangle();
		}
		else
		{
			Vector2 topLeft(rect.GetPos());
			Vector2 bottomRight(rect.GetBottomRight());
			Vector2 otherTopLeft(otherRect.GetPos());
			Vector2 otherBottomRight(otherRect.GetBottomRight());

			Vector2 interSectionTopLeft(
				topLeft.GetX() > otherTopLeft.GetX() ? topLeft.GetX() : otherTopLeft.GetX(),
				topLeft.GetY() > otherTopLeft.GetY() ? topLeft.GetY() : otherTopLeft.GetY());
			Vector2 interSectionBottomRight(
				bottomRight.GetX() < otherBottomRight.GetX() ? bottomRight.GetX() : otherBottomRight.GetX(),
				bottomRight.GetY() < otherBottomRight.GetY() ? bottomRight.GetY() : otherBottomRight.GetY());
			Vector2 size(
				interSectionBottomRight.GetX() - interSectionTopLeft.GetX(),
				interSectionBottomRight.GetY() - interSectionTopLeft.GetY());

			return hRectangle(interSectionTopLeft, size);
		}
	}

	hRectangle hRectangle::getUnion(const hRectangle& rect, const hRectangle& otherRect)
	{
		Vector2 topLeft(rect.mPosition);
		Vector2 bottomRight(rect.GetBottomRight());
		Vector2 otherBottomRight(otherRect.GetBottomRight());

		topLeft.SetX(topLeft.GetX() < otherRect.mPosition.GetX() ? topLeft.GetX() : otherRect.mPosition.GetX());
		topLeft.SetY(topLeft.GetY() < otherRect.mPosition.GetY() ? topLeft.GetY() : otherRect.mPosition.GetY());

		bottomRight.SetX(bottomRight.GetX() < otherBottomRight.GetX() ? otherBottomRight.GetX() : bottomRight.GetX());
		bottomRight.SetY(bottomRight.GetY() < otherBottomRight.GetY() ? otherBottomRight.GetY() : bottomRight.GetY());

		bottomRight -= topLeft;
		return hRectangle(topLeft, bottomRight);
	}
}