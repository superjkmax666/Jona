#pragma once

#include "Core.h"

#include "Window.h"
#include "Jona/LayerStack.h"
#include "Jona/Events/Event.h"
#include "Jona/Events/ApplicationEvent.h"

#include "Jona/ImGui/ImGuiLayer.h"

#include "Jona/Renderer/Shader.h"
#include "Jona/Renderer/Buffer.h"

namespace Jona {

	class JONA_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();

}
