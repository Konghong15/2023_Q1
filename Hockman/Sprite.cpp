#include "Sprite.h"

namespace hockman
{
	Sprite::Sprite()
		: Sprite(0, 0, nullptr)
	{
	}

	Sprite::Sprite(int width, int height, const char* img)
		: Width(width)
		, Height(height)
		, Img(img)
	{
	}

	Sprite::~Sprite()
	{
		delete Img;
		Img = nullptr;
	}
}