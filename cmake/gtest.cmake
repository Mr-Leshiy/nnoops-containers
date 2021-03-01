find_package(GTest CONFIG REQUIRED)


function(addtest test_name)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)

    add_executable(${test_name} ${ARGN})
    addtest_part(${test_name} ${ARGN})
    target_link_libraries(${test_name}
            GTest::gmock
            GTest::gtest 
            GTest::gmock_main 
            GTest::gtest_main
            Threads::Threads
            )
    add_test(
            NAME ${test_name}
            COMMAND $<TARGET_FILE:${test_name}>
    )
    set_target_properties(${test_name} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED TRUE
            )
    disable_clang_tidy(${test_name})
    if(UNIX)
        # works only on UNIX systems
        target_compile_options(${test_name} PUBLIC
                # we don't care about potential null dereferences in tests
                -Wno-null-dereference
                )
    endif()
endfunction()

function(addtest_part test_name)
    if (POLICY CMP0076)
        cmake_policy(SET CMP0076 NEW)
    endif ()
    target_sources(${test_name} PUBLIC
            ${ARGN}
            )
endfunction()