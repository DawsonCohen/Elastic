#pragma once

#include "Elastic/Application.h"
#include "Elastic/Base.h"

extern Elastic::Application* Elastic::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	Elastic::Log::Init();

	auto app = Elastic::CreateApplication({ argc, argv });

	app->Run();

	delete app;
}