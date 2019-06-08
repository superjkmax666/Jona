#include <Jona.h>

class Sandbox : public Jona::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Jona::Application* Jona::CreateApplication()
{
	return new Sandbox();
}