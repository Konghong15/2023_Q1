#include <cassert>
#include <memory.h>
#include <cmath>

#include "hRectangle.h"

namespace catInWonderland
{
	hRectangle::hRectangle(Vector2 topLeft, Vector2 bottomRight)
	{
		Vector2& memTopLeft = getVertex(eRectangleIndex::TopLeft);
		Vector2& memBottomRight = getVertex(eRectangleIndex::BottomRight);

		memTopLeft = topLeft;
		memBottomRight = bottomRight;

		float temp;
		if (getVertex(eRectangleIndex::TopLeft).GetX() > getVertex(eRectangleIndex::BottomRight).GetX())
		{
			temp = memTopLeft.GetX();
			memTopLeft.SetX(memBottomRight.GetX());
			memBottomRight.SetX(temp);
		}
		if (memTopLeft.GetY() > memBottomRight.GetY())
		{
			temp = memTopLeft.GetY();
			memTopLeft.SetY(memBottomRight.GetY());
			memBottomRight.SetY(temp);
		}

		getVertex(eRectangleIndex::TopRight) = Vector2(memBottomRight.GetX(), memTopLeft.GetY());
		getVertex(eRectangleIndex::BottomLeft) = Vector2(memTopLeft.GetX(), memBottomRight.GetY());
	}

	hRectangle::hRectangle(float x1, float y1, float x2, float y2)
		: hRectangle(Vector2(x1, y1), Vector2(x2, y2))
	{
	}

	hRectangle::hRectangle()
		: hRectangle(0.f, 0.f, 0.f, 0.f)
	{
	}

	void hRectangle::Rotate(const Vector2& origin, float radian)
	{
		// ���� �̵�
		for (size_t i = 0; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
		{
			mVertices[i].Move(-origin.GetX(), -origin.GetY());
		}

		// ȸ��
		{
			float cosScalr = cos(radian);
			float sinScalr = sin(radian);
			Vector2 temp;

			for (size_t i = 0; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
			{
				temp.SetX(mVertices[i].GetX() * cosScalr - mVertices[i].GetY() * sinScalr);
				temp.SetY(mVertices[i].GetX() * sinScalr + mVertices[i].GetY() * cosScalr);
				mVertices[i] = temp;
			}
		}

		// ���� �̵�
		for (size_t i = 0; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
		{
			mVertices[i].Move(origin.GetX(), origin.GetY());
		}
	}

	bool hRectangle::IsCollision(const hRectangle& rect, const hRectangle& otherRect)
	{
		return rect.getVertex(eRectangleIndex::BottomRight).GetX() >= otherRect.getVertex(eRectangleIndex::TopLeft).GetX()
			&& otherRect.getVertex(eRectangleIndex::BottomRight).GetX() >= rect.getVertex(eRectangleIndex::TopLeft).GetX()
			&& rect.getVertex(eRectangleIndex::TopLeft).GetY() <= otherRect.getVertex(eRectangleIndex::BottomRight).GetY()
			&& otherRect.getVertex(eRectangleIndex::TopLeft).GetY() <= rect.getVertex(eRectangleIndex::BottomRight).GetY();
	}

	bool hRectangle::IsContained(const hRectangle& rect, const hRectangle& otherRect)
	{
		return rect.GetTopLeft() < otherRect.GetTopLeft() && rect.GetBottomRight() > otherRect.GetBottomRight();
	}

	hRectangle hRectangle::GetIntersection(const hRectangle& rect, const hRectangle& otherRect)
	{
		assert(IsCollision(rect, otherRect));

		Vector2 interSectionTopLeft(
			rect.GetTopLeft().GetX() > otherRect.GetTopLeft().GetX() ? rect.GetTopLeft().GetX() : otherRect.GetTopLeft().GetX(),
			rect.GetTopLeft().GetY() > otherRect.GetTopLeft().GetY() ? rect.GetTopLeft().GetY() : otherRect.GetTopLeft().GetY());
		Vector2 interSectionBottomRight(
			rect.GetBottomRight().GetX() < otherRect.GetBottomRight().GetX() ? rect.GetBottomRight().GetX() : otherRect.GetBottomRight().GetX(),
			rect.GetBottomRight().GetY() < otherRect.GetBottomRight().GetY() ? rect.GetBottomRight().GetY() : otherRect.GetBottomRight().GetY());

		return hRectangle(interSectionTopLeft, interSectionBottomRight);
	}

	hRectangle hRectangle::GetBoundingRectangle(const hRectangle& rectangle)
	{
		float minX = rectangle.mVertices[0].GetX();
		float minY = rectangle.mVertices[0].GetY();
		float maxX = rectangle.mVertices[0].GetX();
		float maxY = rectangle.mVertices[0].GetY();

		for (size_t i = 1; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
		{
			float x = rectangle.mVertices[i].GetX();
			float y = rectangle.mVertices[i].GetY();

			if (minX > x)
			{
				minX = x;
			}
			else if (maxX < x)
			{
				maxX = x;
			}

			if (minY > y)
			{
				minY = y;
			}
			else if (maxY < y)
			{
				maxY = y;
			}
		}

		return hRectangle(Vector2(minX, minY), Vector2(maxX, maxY));
	}
}