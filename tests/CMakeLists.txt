include(TestUtils)

set(googletest_commit_hash "52eb8108c5bdec04579160ae17225d66034bd723")

fetch_googletest(HASH "${googletest_commit_hash}" HIDDEN)

set(MEMORY_TESTS "")
set(CPU_TESTS "cpu/cpu_register_tests.cpp")

# Wish there was a nicer way to stucture these into indivdual packages
# There may be but .... easier to just do this!
add_executable(
  tanukigb_tests
  ${MEMORY_TESTS}
  ${CPU_TESTS}
  )

target_link_libraries(tanukigb_tests cpu memory GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tanukigb_tests)
