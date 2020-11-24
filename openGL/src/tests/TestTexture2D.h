#pragma once

#include <memory>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace test {
class TestTexture2D : public Test {
 public:
  TestTexture2D();
  ~TestTexture2D();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

 private:
  std::unique_ptr<VertexArray> m_Vao;
  std::unique_ptr<VertexBuffer> m_Vbo;
  std::unique_ptr<IndexBuffer> m_Ibo;
  std::unique_ptr<Shader> m_Shader;
  std::unique_ptr<Texture> m_Texture;

  glm::vec3 m_TranslationA, m_TranslationB;
  glm::mat4 m_Proj, m_View;
};
}  // namespace test