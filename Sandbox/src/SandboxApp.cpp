#include <Jona.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Jona::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Jona::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Jona::Ref<Jona::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jona::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jona::BufferLayout layout = {
			{ Jona::ShaderDataType::Float3, "a_Position" },
			{ Jona::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Jona::Ref<Jona::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jona::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Jona::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Jona::Ref<Jona::VertexBuffer> squareVB;
		squareVB.reset(Jona::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Jona::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Jona::Ref<Jona::IndexBuffer> squareIB;
		squareIB.reset(Jona::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Jona::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderIndexSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Jona::Shader::Create(flatColorShaderVertexSrc, flatColorShaderIndexSrc));
	}

	void OnUpdate(Jona::Timestep ts) override
	{
		if (Jona::Input::IsKeyPressed(JN_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Jona::Input::IsKeyPressed(JN_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Jona::Input::IsKeyPressed(JN_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Jona::Input::IsKeyPressed(JN_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Jona::Input::IsKeyPressed(JN_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Jona::Input::IsKeyPressed(JN_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Jona::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Jona::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Jona::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Jona::OpenGLShader>( m_FlatColorShader )->Bind();
		std::dynamic_pointer_cast<Jona::OpenGLShader>( m_FlatColorShader )->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Jona::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Jona::Renderer::Submit(m_Shader, m_VertexArray);

		Jona::Renderer::EndScene();

		//Renderer::Flush();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Jona::Event& event) override
	{
	}
private:
	Jona::Ref<Jona::Shader> m_Shader;
	Jona::Ref<Jona::VertexArray> m_VertexArray;
	
	Jona::Ref<Jona::Shader> m_FlatColorShader;
	Jona::Ref<Jona::VertexArray> m_SquareVA;

	Jona::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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