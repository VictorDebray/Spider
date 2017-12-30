cmake_minimum_required(VERSION 3.9.2)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
        main.cpp ServerTest.cpp ServerTest.hpp)
set(CMAKE_CXX_STANDARD 17)
include_directories(../../Common)
include_directories(../../Server)

ADD_EXECUTABLE(server_test ${SRCS})

if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif()

set(Boost_DEBUG off)
find_package(Boost 1.65 COMPONENTS system thread serialization REQUIRED)

TARGET_LINK_LIBRARIES(server_test
        libgtest
        ${Boost_LIBRARIES} -lpthread
        )

add_test(NAME server_test
        COMMAND server_test)

install(TARGETS server_test DESTINATION ${PROJECT_SOURCE_DIR}/bin)
