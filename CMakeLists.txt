cmake_minimum_required(VERSION 3.0)
project(sysinfo VERSION 0.5.0)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "No build type provided, setting MinSizeRel")
    set(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING "" FORCE)
endif()

set(SYSINFO_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SYSINFO_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SYSINFO_VERSION_PATCH ${PROJECT_VERSION_PATCH})
configure_file(cmake/version.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/version.hpp)

add_executable(sysinfo main.cpp)
target_include_directories(sysinfo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(sysinfo PROPERTIES CXX_STANDARD 11) # for raw string literals
set_target_properties(sysinfo PROPERTIES CXX_EXTENSIONS OFF)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_compile_definitions(sysinfo PRIVATE SYSINFO_ENABLE_DARWIN)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_compile_definitions(sysinfo PRIVATE SYSINFO_ENABLE_LINUX)
else ()
  message(FATAL "Unsupported system ${CMAKE_SYSTEM_NAME}")
endif()
