include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(sfot-tests
    registerTest.cpp
    decodeTest.cpp
)

target_link_libraries(sfot-tests
    PRIVATE
        sfot_lib
        GTest::gtest_main

)

include(GoogleTest)
gtest_discover_tests(sfot-tests)
