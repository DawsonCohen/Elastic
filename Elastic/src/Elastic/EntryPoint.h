#pragma once

#include "Elastic/Application.h"
#include "Elastic/Log.h"

extern Elastic::Application* Elastic::CreateApplication();

int main(int argc, char** argv)
{
	Elastic::Log::Init();
	EL_CORE_WARN("Initialized Log!");
	int a = 5;
	EL_INFO("Hello! Var={0}", a);

	auto app = Elastic::CreateApplication();
	app->Run();
	delete app;
}