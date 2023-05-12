#pragma once

namespace hockman
{
	class Vector2
	{
	public:
		Vector2();
		~Vector2() = default;
		Vector2(const Vector2&) = default;
		Vector2& operator=(const Vector2&) = default;

		Vector2(float x, float y);

		inline const float& GetX() const;
		inline const float& GetY() const;
		inline void SetX(float x);
		inline void SetY(float y);

		Vector2 GetNormalized() const;
		float GetMagnitude() const;
		Vector2& SetNormalize();
		
		bool operator==(const Vector2& other);
		bool operator<(const Vector2& other);
		bool operator<=(const Vector2& other);
		bool operator>(const Vector2& other);
		bool operator>=(const Vector2& other);

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(float scalar) const;
		Vector2 operator/(float scalar) const;

		void operator+=(const Vector2& other);
		void operator-=(const Vector2& other);
		void operator/=(float scalar);
		void operator*=(float scalar);

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
}