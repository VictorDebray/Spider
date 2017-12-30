cmake_minimum_required(VERSION 3.9.2)

set(CMAKE_CXX_STANDARD 17)

set(DATABASE_DIR Database)
set(BOOST_DIR Boost)
set(COMMON_DIR ../Common/)
set(SPIDER_DIR .)

set(DATABASE_SRC
        ${DATABASE_DIR}/ADatabase.hpp
        ${DATABASE_DIR}/MongoConnector.hpp
        ${DATABASE_DIR}/MongoConnector.cpp
        ${DATABASE_DIR}/Test.cpp
        ${DATABASE_DIR}/Test.hpp
        )

set(COMMON_SRC
        ${COMMON_DIR}/Queue.hpp
        ${COMMON_DIR}/AData.hpp
        ${COMMON_DIR}/Command.hpp
        ${COMMON_DIR}/PacketFactory.cpp
        ${COMMON_DIR}/PacketFactory.hpp
        ${COMMON_DIR}/Header.hpp
        ${COMMON_DIR}/LogInput.hpp
        ${COMMON_DIR}/LogMouse.hpp
        ${COMMON_DIR}/ContainerDevice.hpp
        ${COMMON_DIR}/Serialization.hpp
        ${COMMON_DIR}/UsingClass.hpp
        ${COMMON_DIR}/Print.cpp
        )

set(BOOST_SRC
        ${BOOST_DIR}/Connection.cpp
        ${BOOST_DIR}/Connection.hpp
        ${BOOST_DIR}/Connection.hpp
        ${BOOST_DIR}/Accept.hpp
        ${BOOST_DIR}/Accept.cpp)

set(SPIDER_SRC
        ${SPIDER_DIR}/SpiderClient.cpp
        ${SPIDER_DIR}/SpiderClient.hpp
        ${SPIDER_DIR}/SpiderNetwork.cpp
        ${SPIDER_DIR}/SpiderNetwork.hpp
        ${SPIDER_DIR}/SpiderServer.cpp
        ${SPIDER_DIR}/SpiderServer.hpp
        )

set(SOURCE_FILES main.cpp)

add_executable(server ${SOURCE_FILES} ${BOOST_SRC} ${COMMON_SRC}
        ${SPIDER_SRC} ${DATABASE_SRC})

include_directories(${Boost_INCLUDE_DIRS}
        ${BOOST_DIR} ${COMMON_DIR} ${DATABASE_DIR} .)

if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif(APPLE OR WIN32)
set(Boost_DEBUG off)
find_package(Boost 1.65.1 COMPONENTS system thread serialization REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )


target_link_libraries(server ${Boost_LIBRARIES} -lpthread)

if(APPLE)
	find_package(libmongocxx REQUIRED)
	find_package(libbsoncxx REQUIRED)
	include_directories(${LIBMONGOCXX_INCLUDE_DIR})
	include_directories(${LIBBSONCXX_INCLUDE_DIR})
	include_directories("/usr/local/include/mongocxx/v_noabi")
	include_directories("/usr/local/include/bsoncxx/v_noabi")
	include_directories("/usr/local/include/libmongoc-1.0")
	include_directories("/usr/local/include/libbson-1.0")
	include_directories("/usr/local/lib")
elseif(WIN32)
	find_package(libmongocxx REQUIRED)
	find_package(libbsoncxx REQUIRED)

	include_directories(${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
	link_directories(${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
endif()

target_link_libraries(server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(server ${LIBBSONCXX_LIBRARIES})

install(TARGETS server DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# Link runTests with what we want to test and the GTest and pthread library
