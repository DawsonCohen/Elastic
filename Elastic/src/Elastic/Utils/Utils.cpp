#include "elpch.h"
#include "Elastic/Utils/Utils.h"
#include "Elastic/Core/Application.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

namespace Elastic {

	float Time::GetTime()
	{
		return glfwGetTime();
	}

}
