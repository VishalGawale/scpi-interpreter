add_executable(test_scpi test_scpi.cpp)
target_link_libraries(test_scpi PRIVATE scpi_lib)
add_test(NAME scpi_tests COMMAND test_scpi)