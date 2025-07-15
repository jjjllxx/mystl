find_package(GTest REQUIRED)

set(TARGET dsa_test)
set(SOURCES
    ${DSA_CORE_CPPS}
    ${DSA_TEST_CPPS}
    main.cpp
)

include(${PROJECT_SOURCE_DIR}/Algo/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/DS/CMakeLists.txt)

add_executable(${TARGET}
     ${SOURCES})

list(APPEND LIBS GTest::gtest)

target_link_libraries(${TARGET} PRIVATE
    ${LIBS})

target_include_directories(${TARGET} PRIVATE 
    ${PROJECT_SOURCE_DIR}
)

set_target_properties(${TARGET} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)