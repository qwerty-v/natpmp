project(tests C)

set(CMAKE_C_STANDARD 99)

add_executable(test1 unit/options.c
        ../../src/options.c)

add_test(NAME Test1 COMMAND test1)