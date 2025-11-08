
file(GLOB_RECURSE TEST_FILES **.h *.h **.cpp *.cpp)

set(FILE_NAMES)
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME)
    list(APPEND FILE_NAMES ${TEST_FILE_NAME})
endforeach()

create_test_sourcelist(TEST_SOURCE_LIST TestCore.cpp ${FILE_NAMES})

add_executable(TestCore ${TEST_SOURCE_LIST})

target_include_directories(TestCore PRIVATE ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
target_link_libraries(TestCore PRIVATE "${GLFW_LIBRARY_DIR}/glfw3.lib")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    add_test(
      NAME ${TEST_FILE_NAME}
      COMMAND TestCore ${TEST_FILE_NAME}
      )
endforeach()

add_custom_target(BUILD_RUN_TESTS
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
    COMMENT "Running tests output"
)
add_dependencies(BUILD_RUN_TESTS TestCore)

add_custom_target(BUILD_RUN_TESTS_VERBOSE
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
    --verbose
    COMMENT "Running tests with verbose output"
)
add_dependencies(BUILD_RUN_TESTS_VERBOSE TestCore)
