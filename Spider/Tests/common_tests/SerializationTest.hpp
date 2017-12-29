//
// Created by Victor Debray on 01/11/2017.
//

#ifndef PROJECT_SERIALIZATIONTEST_HPP
# define PROJECT_SERIALIZATIONTEST_HPP

# include "TestEnvironment.hpp"
# include "Serialization.hpp"
# include "Command.hpp"
# include "LogInput.hpp"
# include "LogMouse.hpp"
# include "Header.hpp"

namespace {
// Instance creation definition
template<class T>
Sptr<spider::AData> CreatePacket();

template<>
Sptr<spider::AData> CreatePacket<spider::Command>() {
  return std::make_shared<spider::Command>(TestEnvironment::ID,
                                           TestEnvironment::TIME_STAMP,
                                           TestEnvironment::COMMAND_STRING);
}

template<>
Sptr<spider::AData> CreatePacket<spider::LogInput>() {
  return std::make_shared<spider::LogInput>(TestEnvironment::ID,
                                            TestEnvironment::TIME_STAMP,
                                            TestEnvironment::WINDOW_NAME,
                                            TestEnvironment::LOG_MSG);
}

template<>
Sptr<spider::AData> CreatePacket<spider::LogMouse>() {
  return std::make_shared<spider::LogMouse>(TestEnvironment::ID,
                                            TestEnvironment::TIME_STAMP, TestEnvironment::WINDOW_NAME,
                                            TestEnvironment::WIN_SIZE, TestEnvironment::MOUSE_COORD);
}

template<class T>
class SerializationTest : public ::testing::Test {
 protected:
  Sptr<spider::AData> obj_;

 protected:
  SerializationTest() : Test(), obj_(CreatePacket<T>()) {}
  ~SerializationTest() override = default;

  void TearDown() override {
  }

  void SetUp() override {
  }

  template<typename C>
  Sptr<C> serializeDeserialize(spider::Type_e type, C obj) {
    spider::Serialization Serial;
    Sptr<RawPacket> objSer = Serial.serialize<C>(obj);

    auto header = std::make_shared<spider::Header>(objSer->size(), type);
    Sptr<RawPacket> headerCommandSer = Serial.serialize<spider::Header>(*header);

    auto objDeser = Serial.deserialize<C>(*objSer);
    return objDeser;
  }

  //MockServer m_server_;
};
}

#endif //PROJECT_SERIALIZATIONTEST_HPP
