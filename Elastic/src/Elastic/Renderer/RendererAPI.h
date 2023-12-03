#pragma once

#include "Elastic/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Elastic {

	class RendererAPI
	{
	public:
		enum class API
		{
			None, OpenGL = 1
		};
	public:
		virtual ~RendererAPI() = default;

		virtual void Init();
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void SetClearColor(const glm::vec4& color);
		virtual void Clear();

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount);
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount);
		
		virtual void SetLineWidth(float width);

		static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};

}
