cmake_minimum_required(VERSION 3.7)
project(survival)

set(CMAKE_CXX_STANDARD 14)

set(
        SOURCE_FILES
        main.cpp
        glad.c
)
add_executable(survival ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)

target_link_libraries(
        survival

        glfw
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

include_directories(
        ${CMAKE_SOURCE_DIR}/deps/glfw/include
        ${CMAKE_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIRS}
)