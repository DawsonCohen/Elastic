#pragma once

#include "Elastic/Base.h"

#include "Elastic/KeyCodes.h"
#include "Elastic/MouseCodes.h"

#include <glm/glm.hpp>

namespace Elastic {
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode keycode);

		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}