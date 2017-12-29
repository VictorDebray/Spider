set(SRCS
        main.cpp ServerTest.cpp ServerTest.hpp)
set(CMAKE_CXX_STANDARD 17)
include_directories(../../Common)
include_directories(../../Server)

ADD_EXECUTABLE(server_test ${SRCS})
find_package(Boost 1.65 COMPONENTS system thread serialization REQUIRED)

TARGET_LINK_LIBRARIES(server_test
        libgtest
        ${Boost_LIBRARIES} -lpthread
        )

add_test(NAME server_test
        COMMAND server_test)

install(TARGETS server_test DESTINATION ${PROJECT_SOURCE_DIR}/bin)
