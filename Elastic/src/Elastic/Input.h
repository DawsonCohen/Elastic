#pragma once

#include "Elastic/Base.h"

#include "Elastic/KeyCodes.h"
#include "Elastic/MouseCodes.h"

namespace Elastic {
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode keycode);

		static bool IsMouseButtonPressed(const MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}