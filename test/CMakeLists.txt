add_definitions(-DTEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(test_json test_json.cpp)
target_link_libraries(test_json JSON)
add_test(test_json test_json)
