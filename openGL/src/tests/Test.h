#pragma once

namespace test {

class Test {
 public:
  Test() {}
  virtual ~Test() {}
  virtual void OnUpdate(float deltaTime) {}
  virtual void OnRender() {}
  virtual void OnImGuiRender() {}
};


class TestMenu : public Test {
 public:
  TestMenu();
  ~TestMenu();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

};


}  // namespace test