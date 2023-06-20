cmake_minimum_required(VERSION 3.12)

project("Cryptography_Dev")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
  message(STATUS "OpenSSL found: ${OPENSSL_VERSION}")
else()
  message(FATAL_ERROR "OpenSSL not found: ${OPENSSL_VERSION}")
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

include_directories(inc)
add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(executables)


