#pragma once

#include "Elastic/Renderer/Camera.h"
#include "Elastic/Core/Timestep.h"

#include "Elastic/Events/ApplicationEvent.h"
#include "Elastic/Events/KeyEvent.h"
#include "Elastic/Events/MouseEvent.h"

#include <iostream>

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

		const glm::vec3& GetPosition(const glm::vec3& pos) { return m_Camera.GetPosition(); }
		inline void SetDistance(float distance) { m_Camera.SetDistance(distance); }
		// Sets FocalPoint such that the camera is at pos
		// with the same orientation and distance
		inline void SetPosition(const glm::vec3& pos) {
			m_Camera.SetFocalPoint(pos + m_Camera.GetForwardDirection() * m_Camera.GetDistance());
		}

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}