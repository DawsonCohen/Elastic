#include <Elastic.h>
#include "imgui/imgui.h"

class ExampleLayer : public Elastic::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate(Elastic::Timestep ts) override
	{
	}

	void OnEvent(Elastic::Event& event) override
	{
		// EL_TRACE("{0}", event);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

};

class Sandbox : public Elastic::Application
{
public:
	Sandbox(const Elastic::ApplicationSpecification& specification)
		: Elastic::Application(specification)
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}

};

Elastic::Application* Elastic::CreateApplication(Elastic::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Evodevo";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}