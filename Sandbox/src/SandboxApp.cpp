#include <Jona.h>

#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
	}

	~Sandbox()
	{

	}
};

Jona::Application* Jona::CreateApplication()
{
	return new Sandbox();
}