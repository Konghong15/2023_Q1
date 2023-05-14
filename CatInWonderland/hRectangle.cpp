#include <memory.h>

#include "hRectangle.h"

namespace catInWonderland
{
	hRectangle::hRectangle()
		: hRectangle(0.f, 0.f, 0.f, 0.f)
	{
	}

	hRectangle::hRectangle(Vector2 topLeft, Vector2 bottomRight)
		: mTopLeft(topLeft)
		, mBottomRight(bottomRight)
	{
		float temp;
		if (mTopLeft.GetX() > mBottomRight.GetX())
		{
			temp = mTopLeft.GetX();
			mTopLeft.SetX(mBottomRight.GetX());
			mBottomRight.SetX(temp);
		}
		if (mTopLeft.GetY() > mBottomRight.GetY())
		{
			temp = mTopLeft.GetY();
			mTopLeft.SetY(mBottomRight.GetY());
			mBottomRight.SetY(temp);
		}
	}

	hRectangle::hRectangle(float x1, float y1, float x2, float y2)
		: mTopLeft(x1, y1)
		, mBottomRight(x2, y2)
	{
	}

	bool hRectangle::IsCollision(const hRectangle& rect, const hRectangle& otherRect)
	{
		return rect.mBottomRight.GetX() >= otherRect.mTopLeft.GetX() && otherRect.mBottomRight.GetX() >= rect.mTopLeft.GetX()
			&& rect.mTopLeft.GetY() <= otherRect.mBottomRight.GetY() && otherRect.mTopLeft.GetY() <= rect.mBottomRight.GetY();
	}

	bool hRectangle::IsContained(const hRectangle& rect, const hRectangle& otherRect)
	{
		return rect.GetTopLeft() < otherRect.GetTopLeft() && rect.GetBottomRight() > otherRect.GetBottomRight();
	}

	hRectangle hRectangle::GetIntersection(const hRectangle& rect, const hRectangle& otherRect)
	{
		if (!IsCollision(rect, otherRect))
		{
			return hRectangle();
		}
		else
		{
			Vector2 interSectionTopLeft(
				rect.GetTopLeft().GetX() > otherRect.GetTopLeft().GetX() ? rect.GetTopLeft().GetX() : otherRect.GetTopLeft().GetX(),
				rect.GetTopLeft().GetY() > otherRect.GetTopLeft().GetY() ? rect.GetTopLeft().GetY() : otherRect.GetTopLeft().GetY());
			Vector2 interSectionBottomRight(
				rect.GetBottomRight().GetX() < otherRect.GetBottomRight().GetX() ? rect.GetBottomRight().GetX() : otherRect.GetBottomRight().GetX(),
				rect.GetBottomRight().GetY() < otherRect.GetBottomRight().GetY() ? rect.GetBottomRight().GetY() : otherRect.GetBottomRight().GetY());

			return hRectangle(interSectionTopLeft, interSectionBottomRight);
		}
	}

	hRectangle hRectangle::getUnion(const hRectangle& rect, const hRectangle& otherRect)
	{
		/*	Vector2 topLeft(rect.mPosition);
			Vector2 bottomRight(rect.GetBottomRight());
			Vector2 otherBottomRight(otherRect.GetBottomRight());

			topLeft.SetX(topLeft.GetX() < otherRect.mPosition.GetX() ? topLeft.GetX() : otherRect.mPosition.GetX());
			topLeft.SetY(topLeft.GetY() < otherRect.mPosition.GetY() ? topLeft.GetY() : otherRect.mPosition.GetY());

			bottomRight.SetX(bottomRight.GetX() < otherBottomRight.GetX() ? otherBottomRight.GetX() : bottomRight.GetX());
			bottomRight.SetY(bottomRight.GetY() < otherBottomRight.GetY() ? otherBottomRight.GetY() : bottomRight.GetY());

			bottomRight -= topLeft;
			return hRectangle(topLeft, bottomRight);*/
		return hRectangle();
	}
}