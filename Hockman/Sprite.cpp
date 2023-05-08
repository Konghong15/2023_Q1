#include "Sprite.h"

namespace hockman
{

	Sprite::Sprite(HDC hdc, HBITMAP bitmap, BITMAP bitInfo)
		: Hdc(hdc)
		, Bitmap(bitmap)
		, BitInfo(bitInfo)
	{
	}

	Sprite::~Sprite()
	{
		DeleteDC(Hdc);
		DeleteObject(Bitmap);
	}
}