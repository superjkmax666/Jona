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
		if (Jona::Input::IsKeyPressed(JN_KEY_TAB))
			JN_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Jona::Event& event) override
	{
		if (event.GetEventType() == Jona::EventType::KeyPressed)
		{
			Jona::KeyPressedEvent& e = (Jona::KeyPressedEvent&)event;
			if (e.GetKeyCode() == JN_KEY_TAB)
				JN_TRACE("Tab key is pressed (event)!");
			JN_TRACE("{0}", (char) e.GetKeyCode());
		}
	}
};

class Sandbox : public Jona::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Jona::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Jona::Application* Jona::CreateApplication()
{
	return new Sandbox();
}