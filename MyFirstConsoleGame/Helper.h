#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	class Object;

	class Helper
	{
	public:
		static int Clamp(int min, int max, int num);
		static void Spawn(Object* monster, SHORT x, SHORT y, SHORT sizeX, SHORT sizeY);

	public:
		enum { MAP_WIDTH = 400 };
		enum { MAP_HEIGHT = 67 };
	};
}