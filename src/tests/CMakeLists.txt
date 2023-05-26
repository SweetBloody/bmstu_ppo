project(tests)

# Нужно создать папку lib и туда пихнуть gtest
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR})

add_executable(tests_run main_test.cpp)
target_link_libraries(tests_run business_logic data_access gtest gtest_main)
