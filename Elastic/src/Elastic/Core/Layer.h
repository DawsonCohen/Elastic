#pragma once

#include "Elastic/Core/Base.h"
#include "Elastic/Core/Timestep.h"
#include "Elastic/Events/Event.h"
// #include "imgui/imgui.h"

namespace Elastic {

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}