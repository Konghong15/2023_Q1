#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	class Object;
	class Effect;

	class Helper
	{
	public:
		static int Clamp(int min, int max, int num);
		static void Spawn(Object* object, SHORT sizeX, SHORT sizeY);

	public:
		enum { MAP_WIDTH = 1600 };
		enum { MAP_HEIGHT = 67 };
	};
}