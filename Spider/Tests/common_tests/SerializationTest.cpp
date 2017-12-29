#include "SerializationTest.hpp"

typedef testing::Types<spider::Command, spider::LogMouse, spider::LogInput> Implementations;

TYPED_TEST_CASE(SerializationTest, Implementations);

TYPED_TEST(SerializationTest, CommandTest) {
  auto packet = this->serializeDeserialize(spider::COMMAND, *this->obj_);
  EXPECT_EQ(packet->getTimeStamp(), TestEnvironment::TIME_STAMP);
}