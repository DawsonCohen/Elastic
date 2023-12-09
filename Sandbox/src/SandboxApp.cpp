#include <Elastic.h>

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
	spec.WorkingDirectory = "Sandbox";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}

int main(int argc, char** argv)
{
	Elastic::Log::Init();

	EL_PROFILE_BEGIN_SESSION("Startup", "ElasticProfile-Startup.json");
	auto app = Elastic::CreateApplication({ argc, argv });
	EL_PROFILE_END_SESSION();

	EL_PROFILE_BEGIN_SESSION("Runtime", "ElasticProfile-Runtime.json");
	app->Run();
	EL_PROFILE_END_SESSION();

	EL_PROFILE_BEGIN_SESSION("Shutdown", "ElasticProfile-Shutdown.json");
	delete app;
	EL_PROFILE_END_SESSION();
}