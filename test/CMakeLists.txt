find_package(GTest REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/mystl/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/extensions/CMakeLists.txt)

set(TARGET mystl_test)
set(SOURCES
    ${MYSTL_CORE_CPPS}
    ${MYSTL_TEST_CPPS}
    main.cpp
)

include(${PROJECT_SOURCE_DIR}/extensions/CMakeLists.txt)

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