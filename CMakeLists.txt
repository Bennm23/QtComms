cmake_minimum_required(VERSION 3.5)

project(QtComms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


set(ZMQ_INCLUDE_DIRS /usr/include)
set(ZMQ_LIBRARIES /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/libzmq.so)

set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/pkgconfig)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

add_subdirectory(proto)
add_subdirectory(comms)
add_subdirectory(control)
add_subdirectory(backend)
