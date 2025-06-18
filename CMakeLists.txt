cmake_minimum_required(VERSION 3.21)
project(DSA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-pragmas -Wno-comment")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DSA_TARGET dsa)

include(DS/CMakeLists.txt)

set(DSA_SOURCES
    ${DSA_CORE_CPPS}
    main.cpp
)

add_executable(${DSA_TARGET} ${DSA_SOURCES})

set_target_properties(${DSA_TARGET} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if (DSA_TEST)
    add_subdirectory("Test")
endif()