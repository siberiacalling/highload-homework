cmake_minimum_required(VERSION 3.10)
project(http-server)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.65.1 REQUIRED COMPONENTS system filesystem thread)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(SYSTEM ${Boost_LIBRARY_DIRS})
add_executable(http-server ${server_SRC} src/server/connection.cpp src/server/connection.hpp src/server/server.cpp src/server/server.hpp src/server/reply.cpp src/server/request.hpp src/server/request_handler.cpp src/server/request_handler.hpp src/server/reply.hpp src/server/mime_types.cpp src/server/mime_types.hpp src/server/posix_main.cpp src/server/win_main.cpp src/server/request_parser.cpp src/server/request_parser.hpp src/server/config.cpp src/server/config.hpp)

target_link_libraries(http-server ${Boost_LIBRARIES})