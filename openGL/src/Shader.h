#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct shaderProgramSouce {
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader {
 private:
  std::string m_filepath;
  unsigned int m_RendererID;
  // caching system
  std::unordered_map<std::string, int> m_UniformCacheLocation;

 public:
  Shader(const std::string&);
  ~Shader();

  void SetUnifrom1i(const std::string& name, int value);
  void SetUnifrom1f(const std::string& name, float value);
  void SetUnifrom4f(const std::string& name, float v0, float v1, float v2,
                    float v3);
  void SetUnifromMat4f(const std::string& name, const glm::mat4& matrix);

  void Bind() const;
  void Unbind() const;

 private:
  unsigned int createShader(const std::string& vertexShader,
                            const std::string& fragmentShader);
  shaderProgramSouce parseShader(const std::string& filepath);
  unsigned int compileShader(unsigned int type, const std::string& source);
  int GetUniformLocation(const std::string& name);
};