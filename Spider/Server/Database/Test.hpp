#pragma once

#include <string>
class AData {
 public:
  AData() = default;
  virtual ~AData() = default;
  std::string id_;
  int timeStamp_{};
  std::string ipExtern_;
  std::string ipLocal_;
};

class LogMouse : public AData {
 public:
  LogMouse() = default;
  std::string windowName_;
  std::pair<int, int> windowSize_;
  std::pair<int, int> mouseCoord_;
};

class LogInput : public AData {
 public:
  LogInput() = default;
  std::string windowName_;
  std::string input_;
};