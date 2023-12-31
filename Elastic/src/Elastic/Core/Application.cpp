#include "elpch.h"
#include "Elastic/Core/Application.h"

#include "Elastic/Core/Log.h"
#include "Elastic/Renderer/Renderer.h"

#include "Elastic/Core/Input.h"
#include "Elastic/Utils/Utils.h"

namespace Elastic {
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		EL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		m_Window = Window::Create(WindowProps(m_Specification.Name));
		m_Window->SetEventCallback(EL_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::SubmitToMainThread(const std::function<void()>& function)
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		m_MainThreadQueue.emplace_back(function);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EL_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(EL_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(EL_BIND_EVENT_FN(Application::OnKeyPressed));
		
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled) 
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		EL_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			ExecuteMainThreadQueue();
			
			{
				EL_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			{
				EL_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
				
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		EL_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		EL_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
			return false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		EL_PROFILE_FUNCTION();

		if(e.GetKeyCode() == Key::Escape)
			m_Running = false;
		
		return false;
	}

	void Application::ExecuteMainThreadQueue()
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);

		for (auto& func : m_MainThreadQueue)
			func();

		m_MainThreadQueue.clear();
	}

}