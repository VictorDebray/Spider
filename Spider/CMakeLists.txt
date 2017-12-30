cmake_minimum_required(VERSION 3.9.2)

if (APPLE OR UNIX)
	add_subdirectory(Tests)
endif(APPLE OR UNIX)
if (WIN32)
	add_subdirectory(Client)
endif(WIN32)
add_subdirectory(Server)
