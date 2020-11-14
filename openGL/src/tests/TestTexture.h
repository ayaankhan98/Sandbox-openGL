#pragma once

#include "Test.h"

namespace test {
class TestTexture : public Test {
 public:
  TestTexture();
  ~TestTexture();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
}  // namespace test