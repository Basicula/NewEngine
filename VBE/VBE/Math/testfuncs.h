#pragma once

#include <vector>
#include <algorithm>

#include "../math/vector2.h"

namespace Engine
{
	namespace Graph
	{
		float square(float x);
		std::vector<Math::Vector2> lineInterpolation(const std::vector<Math::Vector2> &dots);
		std::vector<Math::Vector2> polyInterpolation(const std::vector<Math::Vector2> &dots);
		std::vector<Math::Vector2> cubeSplainInterpolation(const std::vector<Math::Vector2> &dots);
		std::vector<Math::Vector2> interpolationLagrange(const std::vector<Math::Vector2>& dots);
		std::vector<Math::Vector2> nInterpolation(const std::vector<Math::Vector2> &dots);
	}
}
