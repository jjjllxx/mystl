cmake_minimum_required(VERSION 3.21)
project(MYSTL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MYSTL_TARGET mystl)

include(extensions/CMakeLists.txt)

set(MYSTL_SOURCES
    ${MYSTL_CORE_CPPS}
    main.cpp
)

add_executable(${MYSTL_TARGET} ${MYSTL_SOURCES})
target_include_directories(${MYSTL_TARGET} PUBLIC ${PROJECT_SOURCE_DIR})

set_target_properties(${MYSTL_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if (MYSTL_TEST)
    add_subdirectory("test")
endif()