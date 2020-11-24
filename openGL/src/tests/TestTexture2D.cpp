#include "TestTexture2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

test::TestTexture2D::TestTexture2D()
    : m_TranslationA(200.0f, 100.0f, 0.0f),
      m_TranslationB(400.0f, 100.0f, 0.0f),
      m_Proj(glm::ortho(0.0f, 500.0f, 0.0f, 700.0f, -1.0f, 1.0f)),
      m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))) {
  float positions[] = {0.0f,   0.0f,   0.0f, 0.0f, 100.0f, 0.0f,   1.0f, 0.0f,
                       100.0f, 100.0f, 1.0f, 1.0f, 0.0f,   100.0f, 0.0f, 1.0f};

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  GLCall(glEnable(GL_BLEND));
  GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  m_Vao = std::make_unique<VertexArray>();

  m_Vbo = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(2);
  m_Vao->AddBuffer(*m_Vbo, layout);

  m_Ibo = std::make_unique<IndexBuffer>(indices, 6);

  m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
  m_Shader->Bind();
  m_Texture = std::make_unique<Texture>("res/textures/mario.png");
  m_Shader->SetUnifrom1i("u_Texture", 0);
}

test::TestTexture2D::~TestTexture2D() {}

void test::TestTexture2D::OnUpdate(float deltaTime) {}

void test::TestTexture2D::OnRender() {
  GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
  GLCall(glClear(GL_COLOR_BUFFER_BIT));

  Renderer renderer;

  m_Texture->Bind();

  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
    glm::mat4 mvp = m_Proj * m_View * model;
    m_Shader->Bind();
    m_Shader->SetUnifromMat4f("u_MVP", mvp);
    renderer.Draw(*m_Vao, *m_Ibo, *m_Shader);
  }

  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
    glm::mat4 mvp = m_Proj * m_View * model;
    m_Shader->SetUnifromMat4f("u_MVP", mvp);
    renderer.Draw(*m_Vao, *m_Ibo, *m_Shader);
  }
}

void test::TestTexture2D::OnImGuiRender() {
  ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 900.0f);
  ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 900.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}