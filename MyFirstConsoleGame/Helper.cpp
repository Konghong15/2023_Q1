#include "Helper.h"

namespace hongpireSurvivors
{

	int Helper::Clamp(int min, int max, int num)
	{
		num = min > num ? min : num;
		num = max < num ? max : num;

		return num;
	}
}