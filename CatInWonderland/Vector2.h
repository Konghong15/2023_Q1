#pragma once

namespace catInWonderland
{
	class Vector2
	{
	public:
		Vector2();
		~Vector2() = default;
		Vector2(const Vector2&) = default;
		Vector2& operator=(const Vector2&) = default;

		Vector2(float x, float y);

		inline void Move(float x, float y);

		bool operator==(const Vector2& other) const;
		bool operator<(const Vector2& other) const;
		bool operator<=(const Vector2& other) const;
		bool operator>(const Vector2& other) const;
		bool operator>=(const Vector2& other) const;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(float scalar) const;
		Vector2 operator/(float scalar) const;

		void operator+=(const Vector2& other);
		void operator-=(const Vector2& other);
		void operator/=(float scalar);
		void operator*=(float scalar);

		inline const float& GetX() const;
		inline const float& GetY() const;
		Vector2 GetNormalized() const;
		float GetMagnitude() const;

		inline void SetX(float x);
		inline void SetY(float y);
		Vector2& SetNormalize();

		static float GetDistance(const Vector2& vector, const Vector2& otherVector);

	private:
		float mX;
		float mY;
	};

	const float& Vector2::GetX() const
	{
		return mX;
	}

	const float& Vector2::GetY() const
	{
		return mY;
	}

	void Vector2::SetX(float x)
	{
		mX = x;
	}

	void Vector2::SetY(float y)
	{
		mY = y;
	}

	void Vector2::Move(float x, float y)
	{
		mX += x;
		mY += y;
	}
}