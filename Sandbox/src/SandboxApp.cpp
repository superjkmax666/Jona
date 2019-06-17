#include <Jona.h>

class ExampleLayer : public Jona::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		JN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Jona::Event& event) override
	{
		JN_TRACE("{0}", event);
	}
};

class Sandbox : public Jona::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Jona::Application* Jona::CreateApplication()
{
	return new Sandbox();
}