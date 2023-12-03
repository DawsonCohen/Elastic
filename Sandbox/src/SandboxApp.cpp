#include <Elastic.h>
#include <Elastic/EntryPoint.h>

#include "ExampleLayer.h"

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
	spec.WorkingDirectory = "Sandbox";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}