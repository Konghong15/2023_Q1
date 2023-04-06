#pragma once

namespace hongpireSurvivors
{
	class Helper
	{
	public:
		static int Clamp(int min, int max, int num);

	public:
		enum { MAP_WIDTH = 400 };
		enum { MAP_HEIGHT = 67 };
	};
}