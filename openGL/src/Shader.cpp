#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Renderer.h"

Shader::Shader(const std::string& filepath)
    : m_RendererID(0), m_filepath(filepath) {
  shaderProgramSouce source = parseShader(filepath);
  GLCall(m_RendererID =
             createShader(source.vertexShader, source.fragmentShader));
}

Shader::~Shader() { GLCall(glDeleteProgram(m_RendererID)); }

shaderProgramSouce Shader::parseShader(const std::string& filepath) {
  std::ifstream stream(filepath);

  enum class shaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  shaderType type = shaderType::NONE;
  std::stringstream ss[2];
  std::string line;
  while (std::getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = shaderType::VERTEX;
      }
      if (line.find("fragment") != std::string::npos) {
        type = shaderType::FRAGMENT;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }
  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(unsigned int type,
                                   const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  // Error Handling
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
              << "shader\n";
    std::cout << message << "\n";
    glDeleteShader(id);
    return 0;
  }

  return id;
}

unsigned int Shader::createShader(const std::string& vertexShader,
                                  const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  // glDetachShader() --> have a look at these functions from docs.gl
  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

int Shader::GetUniformLocation(const std::string& name) {
  if (m_UniformCacheLocation.find(name) != m_UniformCacheLocation.end()) {
    return m_UniformCacheLocation[name];
  }
  GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: Uniform " << name << "Doesn't exist";
  }
  m_UniformCacheLocation[name] = location;
  return location;
}

void Shader::SetUnifrom1i(const std::string& name, int value) {
  GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUnifrom1f(const std::string& name, float value) {
  GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUnifrom4f(const std::string& name, float v0, float v1, float v2,
                          float v3) {
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUnifromMat4f(const std::string& name, const glm::mat4& matrix) {
  GLCall(glUniformMatrix4fv(GetUniformLocation(name),1, GL_FALSE, &matrix[0][0]));
}

void Shader::Bind() const { GLCall(glUseProgram(m_RendererID)); }

void Shader::Unbind() const { GLCall(glUseProgram(0)); }