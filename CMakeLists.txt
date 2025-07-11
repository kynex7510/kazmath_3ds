cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
project(kazmath C)

option(KAZMATH_BUILD_GL_UTILS "Build GL utils" ON)

set(KAZMATH_SOURCES
    Source/mat4.c
    Source/mat3.c
    Source/plane.c
    Source/vec4.c
    Source/quaternion.c
    Source/vec2.c
    Source/vec3.c
    Source/aabb2.c
    Source/aabb3.c
    Source/ray2.c
    Source/ray3.c
    Source/3ds.c
)

if (KAZMATH_BUILD_GL_UTILS)
    set(KAZMATH_SOURCES
        ${KAZMATH_SOURCES}
        Source/GL/mat4stack.c
        Source/GL/matrix.c
    )
endif()

add_library(kazmath STATIC ${KAZMATH_SOURCES})
target_compile_options(kazmath PRIVATE "-Wall")
target_include_directories(kazmath PUBLIC Include)

install(TARGETS kazmath)
install(DIRECTORY Include/ DESTINATION include)