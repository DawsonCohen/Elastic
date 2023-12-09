#include <Elastic.h>
#include "Elastic/Core/EntryPoint.h"

#include "Sandbox2D.h"

class Sandbox : public Elastic::Application
{
public:
	Sandbox(const Elastic::ApplicationSpecification& specification)
		: Elastic::Application(specification)
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}

};

Elastic::Application* Elastic::CreateApplication(Elastic::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = ".";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}