#include "elpch.h"
#include "Elastic/Renderer/RendererAPI.h"

#include <glad/glad.h>
#include <csignal>

// void GLClearError() {
//     while(glGetError());
// }

// bool GLLogCall(const char* function, const char* file, int line) {
//     while (GLenum error = glGetError()) {
//         std::cout << "[OpenGL Error] (0x" << std::hex << error << "): " << function <<
// 			" " << file <<	":" << std::dec << line << std::endl;
//         return false;
//     }
//     return true;
// }

// #define ASSERT(x) if (!(x)) std::raise(SIGINT);
// #define GLCall(x) GLClearError();\
// 	x;\
// 	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

namespace Elastic {
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         EL_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       EL_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          EL_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: EL_CORE_TRACE(message); return;
		}
		
		EL_CORE_ASSERT(false, "Unknown severity level!");
	}

	Scope<RendererAPI> RendererAPI::Create()
	{
		return CreateScope<RendererAPI>();
	}

	void RendererAPI::Init()
	{
	#ifdef EL_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void RendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void RendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void RendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}


}