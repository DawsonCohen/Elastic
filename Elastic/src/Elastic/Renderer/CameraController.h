#pragma once

#include "Elastic/Renderer/Camera.h"
#include "Elastic/Core/Timestep.h"

#include "Elastic/Events/ApplicationEvent.h"
#include "Elastic/Events/KeyEvent.h"
#include "Elastic/Events/MouseEvent.h"

namespace Elastic {

	class CameraController
	{
	public:
		CameraController();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraOrientation = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}