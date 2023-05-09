#include <cmath>
#include <limits>

#include "Vector2.h"

namespace hockman
{
	Vector2::Vector2()
		: mX(0)
		, mY(0)
	{
	}

	Vector2::Vector2(float x, float y)
		: mX(x)
		, mY(y)
	{
	}

	Vector2 Vector2::GetNormalized() const
	{
		float magnitude = GetMagnitude();
		return Vector2(mX / magnitude, mY / magnitude);
	}

	float Vector2::GetMagnitude() const
	{
		return sqrt(mX * mX + mY * mY);
	}

	Vector2& Vector2::SetNormalize()
	{
		float magnitude = GetMagnitude();
		mX /= magnitude;
		mY /= magnitude;

		return *this;
	}

	bool Vector2::operator==(const Vector2& other)
	{
		return fabs(mX - other.mX) < FLT_EPSILON && fabs(mY - other.mY) < FLT_EPSILON;
	}

	bool Vector2::operator<(const Vector2& other)
	{
		return (mX - other.mX) < FLT_EPSILON && (mY - other.mY) < FLT_EPSILON;
	}

	bool Vector2::operator<=(const Vector2& other)
	{
		return this->operator<(other) || this->operator==(other);
	}

	bool Vector2::operator>(const Vector2& other)
	{
		return !this->operator<=(other);
	}

	bool Vector2::operator>=(const Vector2& other)
	{
		return !this->operator<(other);
	}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(mX + other.mX, mY + other.mY);
	}

	Vector2 Vector2::operator-(const Vector2& other)const
	{
		return Vector2(mX - other.mX, mY - other.mY);
	}

	Vector2 Vector2::operator*(float scalar)const
	{
		return Vector2(mX * scalar, mY * scalar);
	}

	Vector2 Vector2::operator/(float scalar)const
	{
		return Vector2(mX / scalar, mY / scalar);
	}

	void Vector2::operator+=(const Vector2& other)
	{
		mX += other.mX;
		mY += other.mY;
	}

	void Vector2::operator-=(const Vector2& other)
	{
		mX -= other.mX;
		mY -= other.mY;
	}

	void Vector2::operator/=(float scalar)
	{
		mX /= scalar;
		mY /= scalar;
	}

	void Vector2::operator*=(float scalar)
	{
		mX *= scalar;
		mY *= scalar;
	}

	float Vector2::GetDistance(const Vector2& vector, const Vector2& otherVector)
	{
		float x = abs(vector.mX - otherVector.mX);
		float y = abs(vector.mY - otherVector.mY);

		return (x * x + y * y);
	}
}