#include "elpch.h"
#include "Elastic/Renderer/Renderer3D.h"

#include "Elastic/Renderer/VertexArray.h"
#include "Elastic/Renderer/Shader.h"
#include "Elastic/Renderer/UniformBuffer.h"
#include "Elastic/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Elastic {

	struct Renderer3DData
	{
		static const uint32_t MaxVertices = 10000;
		static const uint32_t MaxIndices = 30000;

		Ref<VertexArray> TriangleVertexArray;
		Ref<VertexBuffer> TriangleVertexBuffer;
		Ref<Shader> TriangleShader;

		Ref<VertexArray> LineVertexArray;
		Ref<VertexBuffer> LineVertexBuffer;
		Ref<Shader> LineShader;	
		
		uint32_t TriangleIndexCount = 0;
		Vertex* TriangleVertexBufferBase = nullptr;
		Vertex* TriangleVertexBufferPtr = nullptr;

		uint32_t LineVertexCount = 0;
		Vertex* LineVertexBufferBase = nullptr;
		Vertex* LineVertexBufferPtr = nullptr;

		float LineWidth = 2.0f;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		EL_PROFILE_FUNCTION();

		s_Data.TriangleVertexArray = VertexArray::Create();

		s_Data.TriangleVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Vertex));
		s_Data.TriangleVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"     },
			{ ShaderDataType::Float4, "a_Color"        },
		});
		s_Data.TriangleVertexArray->AddVertexBuffer(s_Data.TriangleVertexBuffer);

		s_Data.TriangleVertexBufferBase = new Vertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.TriangleVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		// Lines
		s_Data.LineVertexArray = VertexArray::Create();

		s_Data.LineVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Vertex));
		s_Data.LineVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    }
		});
		s_Data.LineVertexArray->AddVertexBuffer(s_Data.LineVertexBuffer);
		s_Data.LineVertexBufferBase = new Vertex[s_Data.MaxVertices];

		s_Data.TriangleShader = Shader::Create("assets/shaders/Renderer3D_Triangle.glsl");
		s_Data.LineShader = Shader::Create("assets/shaders/Renderer3D_Line.glsl");

		s_Data.CameraUniformBuffer = CreateRef<UniformBuffer>(sizeof(Renderer3DData::CameraData), 0);
	}

	void Renderer3D::Shutdown()
	{
		EL_PROFILE_FUNCTION();

		delete[] s_Data.TriangleVertexBufferBase;
	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
		EL_PROFILE_FUNCTION();

		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer3DData::CameraData));

		StartBatch();
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		EL_PROFILE_FUNCTION();

		s_Data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer3DData::CameraData));

		StartBatch();
	}

	void Renderer3D::EndScene()
	{
		EL_PROFILE_FUNCTION();

		Flush();
	}

	void Renderer3D::StartBatch()
	{
		s_Data.TriangleIndexCount = 0;
		s_Data.TriangleVertexBufferPtr = s_Data.TriangleVertexBufferBase;

		s_Data.LineVertexCount = 0;
		s_Data.LineVertexBufferPtr = s_Data.LineVertexBufferBase;	
	}

	void Renderer3D::Flush()
	{
		if (s_Data.TriangleIndexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.TriangleVertexBufferPtr - (uint8_t*)s_Data.TriangleVertexBufferBase);
			s_Data.TriangleVertexBuffer->SetData(s_Data.TriangleVertexBufferBase, dataSize);

			s_Data.TriangleShader->Bind();
			RenderCommand::DrawIndexed(s_Data.TriangleVertexArray, s_Data.TriangleIndexCount);
		}

		if (s_Data.LineVertexCount)
		{
			uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.LineVertexBufferPtr - (uint8_t*)s_Data.LineVertexBufferBase);
			s_Data.LineVertexBuffer->SetData(s_Data.LineVertexBufferBase, dataSize);

			s_Data.LineShader->Bind();
			RenderCommand::SetLineWidth(s_Data.LineWidth);
			EL_INFO("Vertex Count: {0}", s_Data.LineVertexCount);
			RenderCommand::DrawLines(s_Data.LineVertexArray, s_Data.LineVertexCount);
		}
	}

	void Renderer3D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer3D::DrawTriangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color)
	{
		s_Data.TriangleVertexBufferPtr->Position = p0;
		s_Data.TriangleVertexBufferPtr->Color = color;
		s_Data.TriangleVertexBufferPtr++;

		s_Data.TriangleVertexBufferPtr->Position = p1;
		s_Data.TriangleVertexBufferPtr->Color = color;
		s_Data.TriangleVertexBufferPtr++;

		s_Data.TriangleVertexBufferPtr->Position = p2;
		s_Data.TriangleVertexBufferPtr->Color = color;
		s_Data.TriangleVertexBufferPtr++;

		s_Data.TriangleIndexCount += 3;
	}

	void Renderer3D::DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color)
	{
		s_Data.LineVertexBufferPtr->Position = p0;
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexBufferPtr->Position = p1;
		s_Data.LineVertexBufferPtr->Color = color;
		s_Data.LineVertexBufferPtr++;

		s_Data.LineVertexCount += 2;
	}

	void Renderer3D::DrawMesh(const Mesh& mesh, const glm::mat4& transform)
	{
		for(const Edge& e : mesh.GetEdges()) {
			Vertex v1 = mesh.GetVertex(e.v1);
			Vertex v2 = mesh.GetVertex(e.v2);
			glm::vec4 color = e.Color;
			
			s_Data.LineVertexBufferPtr->Position = v1.Position;
			s_Data.LineVertexBufferPtr->Color = color;
			s_Data.LineVertexBufferPtr++;

			s_Data.LineVertexBufferPtr->Position = v2.Position;
			s_Data.LineVertexBufferPtr->Color = color;
			s_Data.LineVertexBufferPtr++;
			
			s_Data.LineVertexCount += 2;
		}

		for(const Facet& f : mesh.GetFacets()) {
			Vertex v1 = mesh.GetVertex(f.v1);
			Vertex v2 = mesh.GetVertex(f.v2);
			Vertex v3 = mesh.GetVertex(f.v3);
			glm::vec4 color = f.Color;
			color[3] = f.Color[3] * mesh.GetOpacity();
			
			s_Data.TriangleVertexBufferPtr->Position = v1.Position;
			s_Data.TriangleVertexBufferPtr->Color = color;
			s_Data.TriangleVertexBufferPtr++;

			s_Data.TriangleVertexBufferPtr->Position = v2.Position;
			s_Data.TriangleVertexBufferPtr->Color = color;
			s_Data.TriangleVertexBufferPtr++;

			s_Data.TriangleVertexBufferPtr->Position = v2.Position;
			s_Data.TriangleVertexBufferPtr->Color = color;
			s_Data.TriangleVertexBufferPtr++;

			s_Data.TriangleIndexCount += 3;
		}

	}

	float Renderer3D::GetLineWidth()
	{
		return s_Data.LineWidth;
	}

	void Renderer3D::SetLineWidth(float width)
	{
		s_Data.LineWidth = width;
	}

}
