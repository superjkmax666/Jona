#pragma once

#include "Core.h"

#include "Window.h"
#include "Jona/LayerStack.h"
#include "Jona/Events/Event.h"
#include "Jona/Events/ApplicationEvent.h"

#include "Jona/Core/Timestep.h"

#include "Jona/ImGui/ImGuiLayer.h"

namespace Jona {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();

}
