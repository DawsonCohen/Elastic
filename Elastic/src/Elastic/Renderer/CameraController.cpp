#include "elpch.h"
#include "Elastic/Renderer/CameraController.h"

#include "Elastic/Core/Input.h"
#include "Elastic/Core/KeyCodes.h"

namespace Elastic {

	CameraController::CameraController()
		: m_Camera()
	{
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		EL_PROFILE_FUNCTION();		
		
		m_CameraPosition = {0.0f, 0.0f, 0.0f};

		if(Input::IsKeyPressed(Key::Left))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		if(Input::IsKeyPressed(Key::Right))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::A))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::D))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::S))
		{
			m_CameraPosition.z += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::W))
		{
			m_CameraPosition.z -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::LeftControl))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::Space))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				m_Camera.MousePan(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				m_Camera.MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				m_Camera.MouseZoom(delta.y);
		}

		m_Camera.UpdatePosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void CameraController::OnEvent(Event& e)
	{
	}

}