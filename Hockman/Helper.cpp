#include <cmath>
#include <limits>

#include "Helper.h"

namespace hockman
{
	bool Helper::Equals(float x, float y)
	{
		return abs(x - y) <= std::numeric_limits<float>::epsilon();
	}
}