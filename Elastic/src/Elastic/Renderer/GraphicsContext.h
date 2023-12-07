#pragma once

#include "Elastic/Core/Base.h"
#include "GLFW/glfw3.h"

namespace Elastic {

	class GraphicsContext
	{
	public:
		GraphicsContext(GLFWwindow* windowHandle);
		virtual ~GraphicsContext() = default;

		virtual void Init();
		virtual void SwapBuffers();

		static Scope<GraphicsContext> Create(void* window);
		
	private:
		GLFWwindow* m_WindowHandle;
	};

}