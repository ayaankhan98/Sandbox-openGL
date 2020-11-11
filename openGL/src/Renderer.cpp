#include "Renderer.h"

#include <iostream>

void GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] : " << line << " " << file << " ( " << function
              << " Error Code: " << error << " "
              << " )\n";
    return false;
  }
  return true;
}


void Renderer::Clear() { GLCall(glClear(GL_COLOR_BUFFER_BIT)); }

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
    const Shader& shader) {
  va.Bind();
  ib.Bind();
  GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}