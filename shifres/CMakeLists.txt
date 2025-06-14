cmake_minimum_required(VERSION 3.10)
project(Anton-Gera_CppProject_2sem)
add_executable(main main.cpp)

enable_testing()

add_executable(tests tests.cpp)

add_test(NAME all_tests COMMAND tests)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
)