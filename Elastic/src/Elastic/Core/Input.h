#pragma once

#include "Elastic/Core/Base.h"

#include "Elastic/Core/KeyCodes.h"
#include "Elastic/Core/MouseCodes.h"

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