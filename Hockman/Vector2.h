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