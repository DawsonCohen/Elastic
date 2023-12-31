#include "elpch.h"
#include "Elastic/Renderer/RenderCommand.h"

#include <glad/glad.h>
#include <csignal>

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

	void RenderCommand::Init()
	{
		EL_PROFILE_FUNCTION();

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

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, indexCount);
	}

	void RenderCommand::DrawArrays(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}

	void RenderCommand::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDisable(GL_DEPTH_TEST);
		// glDepthMask(GL_FALSE);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glEnable(GL_DEPTH_TEST);
	}

	void RenderCommand::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

}