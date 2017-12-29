#ifndef TEST_ENVIRONMENT_HPP_
# define TEST_ENVIRONMENT_HPP_

# include "gtest/gtest.h"

class TestEnvironment : public ::testing::Environment {
 public:
  static const std::string ID;
  static const int TIME_STAMP;
  static const std::string COMMAND_STRING;
  static const std::string WINDOW_NAME;
  static const std::string LOG_MSG;
  static const std::pair<int, int> WIN_SIZE;
  static const std::pair<int, int> MOUSE_COORD;
};

#endif