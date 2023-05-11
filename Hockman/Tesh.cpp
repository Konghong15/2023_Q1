#include <cassert>

#include "Test.h"
#include "Helper.h"

namespace hockman
{
	void TestHelper()
	{
		assert(Helper::Equals(0.11f, 0.11f));
	}
}