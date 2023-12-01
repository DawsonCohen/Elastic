#pragma once

#include "Core.h"

namespace Elastic {

	class ELASTIC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}