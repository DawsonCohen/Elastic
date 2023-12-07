#pragma once

#include "Elastic/Core/Layer.h"

#include "Elastic/Events/ApplicationEvent.h"
#include "Elastic/Events/KeyEvent.h"
#include "Elastic/Events/MouseEvent.h"

namespace Elastic {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		
		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
	};

}
