//
// Created by Victor Debray on 01/11/2017.
//

#ifndef PROJECT_SERVERTEST_HPP
# define PROJECT_SERVERTEST_HPP

# include "gtest/gtest.h"
# include "Serialization.hpp"
# include "PacketFactory.hpp"
# include "Command.hpp"
# include "LogInput.hpp"
# include "LogMouse.hpp"

class ServerTest : public ::testing::Test {
 protected:
  spider::Serialization serial_;

 protected:
  ServerTest() : Test() {}
  ~ServerTest() override = default;

  void SetUp() override;
  void TearDown() override;

  //MockServer m_server_;
};

#endif //PROJECT_SERVERTEST_HPP
