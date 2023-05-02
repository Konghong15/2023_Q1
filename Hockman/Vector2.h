#pragma once

class Vector2
{
public:
	Vector2();
	~Vector2();
	Vector2(const Vector2&);
	Vector2& operator=(const Vector2&);

	inline const float& GetX() const;
	inline const float& GetY() const;
	inline void SetX();
	inline void SetY();



private:
	float mX;
	float mY;
};