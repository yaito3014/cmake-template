find_package(Catch2 3 REQUIRED)

function(example_add_test test_name)
    set(target_name example_${test_name}_test)
    add_executable(${target_name} ${test_name}.cpp)
    target_link_libraries(${target_name} PRIVATE example::example)
    target_link_libraries(${target_name} PRIVATE Catch2::Catch2WithMain)
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

example_add_test(main)
