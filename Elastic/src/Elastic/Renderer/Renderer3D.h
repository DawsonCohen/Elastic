#pragma once

#include "Elastic/Renderer/Camera.h"
#include "Elastic/Scene/Mesh.h"

namespace Elastic {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawMesh(const Mesh& mesh, const glm::mat4& transform = glm::mat4(1.0f));
		static void DrawMeshLines(const Mesh& mesh, const glm::mat4& transform = glm::mat4(1.0f));
		static void DrawTriangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color);
		static void DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color);

		static float GetLineWidth();
		static void SetLineWidth(float width);

	private:
		static void StartBatch();
		static void NextBatch();
	};

}
