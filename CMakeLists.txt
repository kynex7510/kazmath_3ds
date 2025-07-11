cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(kazmath C)

option(KAZMATH_BUILD_GL_UTILS "Build GL utils" ON)

set(KAZMATH_SOURCES
    ./kazmath/mat4.c
    ./kazmath/mat3.c
    ./kazmath/plane.c
    ./kazmath/vec4.c
    ./kazmath/quaternion.c
    ./kazmath/vec2.c
    ./kazmath/vec3.c
    ./kazmath/utility.c
    ./kazmath/aabb2.c
    ./kazmath/aabb3.c
    ./kazmath/ray2.c
    ./kazmath/ray3.c
)

if (KAZMATH_BUILD_GL_UTILS)
    set(KAZMATH_SOURCES
        ${KAZMATH_SOURCES}
        ./kazmath/GL/mat4stack.c
        ./kazmath/GL/matrix.c
    )
endif()

add_library(kazmath STATIC ${KAZMATH_SOURCES})
target_compile_options(kazmath "-Wall")
target_include_directories(kazmath PUBLIC kazmath kazmath/GL)

install(TARGETS kazmath)
install(DIRECTORY Include/ DESTINATION include)