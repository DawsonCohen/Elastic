#pragma once

#include "Elastic/Base.h"
#include "Elastic/Events/Event.h"

#include <GLFW/glfw3.h>

namespace Elastic {
	static uint8_t s_GLFWWindowCount = 0;

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool Visible = true;

		WindowProps(const std::string& title = "Elastic Engine",
			        uint32_t width = 1600,
			        uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		inline void* GetNativeWindow() const { return m_Window; }

		static Window* Create(const WindowProps& props = WindowProps());

	private:
		void Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool Visible = true;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};

}