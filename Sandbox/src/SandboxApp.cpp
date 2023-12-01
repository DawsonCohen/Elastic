#include <Elastic.h>

class Sandbox : public Elastic::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Elastic::Application* Elastic::CreateApplication()
{
	return new Sandbox();
}