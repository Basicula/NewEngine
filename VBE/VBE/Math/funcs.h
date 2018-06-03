#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace Engine {

	namespace Math {

		inline float toRadians(float degrees)
		{
			return degrees * (M_PI / 180);
		}

		inline float toDegrees(float radians)
		{
			return (radians * 180) / M_PI;
		}

	}
}

