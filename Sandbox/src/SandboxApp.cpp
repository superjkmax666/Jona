#include <Jona.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const & Rotate) {
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

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