#pragma once

namespace hongpireSurvivors
{
	struct Sprite
	{
	public:
		Sprite();
		Sprite(int width, int height, const char* img);
		~Sprite();

	public:
		const char* Img;
		int Width;
		int Height;
	};
}