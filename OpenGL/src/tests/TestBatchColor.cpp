#include "TestBatchColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestBatchColor::TestBatchColor() :
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			 50.0f, 250.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			150.0f, 250.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			150.0f, 350.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			 50.0f, 350.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,

			250.0f, 250.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			350.0f, 250.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			350.0f, 350.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			250.0f, 350.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
		};
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 7 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
		m_Shader = std::make_unique<Shader>("res/shaders/BatchColor.shader");
		m_Shader->Bind();
	}

	TestBatchColor::~TestBatchColor()
	{
	}

	void TestBatchColor::OnUpdate(float deltaTime)
	{
	}

	void TestBatchColor::OnRender()
	{
		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer m_renderer;

		glm::mat4 mvp = m_Proj * m_View * m_Model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchColor::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}