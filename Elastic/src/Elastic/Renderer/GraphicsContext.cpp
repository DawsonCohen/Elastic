#include "elpch.h"
#include <glad/glad.h>
#include "Elastic/Renderer/GraphicsContext.h"

// #include "Elastic/Renderer/Renderer.h"
#include "Elastic/Core/Base.h"


namespace Elastic {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		return CreateScope<GraphicsContext>(static_cast<GLFWwindow*>(window));
	}

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		EL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void GraphicsContext::Init()
	{
		EL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EL_CORE_ASSERT(status, "Failed to initialize Glad!");

		EL_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Elastic requires at least OpenGL version 4.5!");
	}

	void GraphicsContext::SwapBuffers()
	{
		EL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}