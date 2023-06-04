#pragma once

#include <Windows.h>

namespace catInWonderland
{
	//(경고) struct 표시 문제
	struct Sprite
	{
	public:
		Sprite() = default;
		Sprite(HDC hdc, HBITMAP bitmap, BITMAP bitInfo);
		~Sprite();

	public:
		HDC Hdc;
		HBITMAP Bitmap;
		BITMAP BitInfo;
	};
}