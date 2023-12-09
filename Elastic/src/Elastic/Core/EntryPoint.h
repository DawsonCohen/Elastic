#pragma once

#include "Elastic/Core/Application.h"
#include "Elastic/Core/Base.h"

extern Elastic::Application* Elastic::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Elastic::Log::Init();

	EL_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Elastic::CreateApplication({ argc, argv });
	EL_PROFILE_END_SESSION();

	EL_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	EL_PROFILE_END_SESSION();

	EL_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
	delete app;
	EL_PROFILE_END_SESSION();
}