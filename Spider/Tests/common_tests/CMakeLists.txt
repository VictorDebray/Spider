set(CMAKE_CXX_STANDARD 17)
set(SRCS
        main.cpp
        SerializationTest.hpp SerializationTest.cpp
        TestEnvironment.hpp TestEnvironment.cpp)

include_directories(../../Common .)
enable_testing()

ADD_EXECUTABLE(common_test ${SRCS})

find_package(Boost 1.65 COMPONENTS system thread serialization REQUIRED)

TARGET_LINK_LIBRARIES(common_test
        libgtest
        ${Boost_LIBRARIES} -lpthread
        )

add_test(NAME common_test
        COMMAND common_test)

install(TARGETS common_test DESTINATION ${PROJECT_SOURCE_DIR}/bin)
