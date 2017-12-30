cmake_minimum_required(VERSION 3.9.2)
project(Client)
set(CMAKE_CXX_STANDARD 14)

set(EXCEPTION_DIR Exception)
set(COMMON_DIR ../Common/)
set(SPIDER_DIR .)
set(EXCEPTION_SRC
		${EXCEPTION_DIR}/FileManagerException.cpp
		${EXCEPTION_DIR}/FileManagerException.hpp
		${EXCEPTION_DIR}/KeyloggerException.cpp
		${EXCEPTION_DIR}/KeyloggerException.hpp
		${EXCEPTION_DIR}/NetworkException.cpp
		${EXCEPTION_DIR}/NetworkException.hpp
		${EXCEPTION_DIR}/ProgException.cpp
		${EXCEPTION_DIR}/ProgException.hpp
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

set(SOURCE_FILES
		${SPIDER_DIR}/Client.cpp
		${SPIDER_DIR}/Client.hpp
		${SPIDER_DIR}/ConfigManager.cpp
		${SPIDER_DIR}/ConfigManager.hpp
		${SPIDER_DIR}/CurrentServer.cpp
		${SPIDER_DIR}/CurrentServer.hpp
		${SPIDER_DIR}/Executable.cpp
		${SPIDER_DIR}/Executable.hpp
		${SPIDER_DIR}/FileManager.cpp
		${SPIDER_DIR}/FileManager.hpp
		${SPIDER_DIR}/Keylogger.cpp
		${SPIDER_DIR}/Keylogger.hpp
		${SPIDER_DIR}/OfflineManager.cpp
		${SPIDER_DIR}/OfflineManager.hpp
		${SPIDER_DIR}/PacketLogger.cpp
		${SPIDER_DIR}/PacketLogger.hpp
		${SPIDER_DIR}/main.cpp)
		
add_executable(client ${EXCEPTION_SRC} ${SOURCE_FILES} ${COMMON_SRC})

if (APPLE OR WIN32)
    set(Boost_USE_STATIC_LIBS TRUE)
endif(APPLE OR WIN32)
set(Boost_DEBUG on)
find_package(Boost 1.65.1 COMPONENTS system thread serialization regex REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

include_directories(${Boost_INCLUDE_DIRS}
        ${COMMON_DIR} ${EXCEPTION_DIR} .)

target_link_libraries(client ${Boost_LIBRARIES})

install(TARGETS client DESTINATION ${PROJECT_SOURCE_DIR}/bin)

