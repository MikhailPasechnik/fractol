cmake_minimum_required(VERSION 3.2)

set(NAME fractol)
project(${NAME} C)
find_package(OpenCL REQUIRED)

add_subdirectory(libft)
file(GLOB SRC src/*.c src/ocl/*.c)
find_package(OpenCL REQUIRED)

add_executable(${NAME} ${SRC})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_directories(libft minilibx_macos)
    target_link_libraries(${NAME} libmlx.a m ft ${OpenCL_LIBRARY} "-framework OpenGL" "-framework AppKit")
    target_include_directories(${NAME} PUBLIC libft include minilibx_macos ${OpenCL_INCLUDE_DIRS})
else()
    link_directories(libft minilibx)
    target_link_libraries(${NAME} libmlx.a Xext X11 m ft ${OpenCL_LIBRARY})
    target_include_directories(${NAME} PUBLIC libft include minilibx ${OpenCL_INCLUDE_DIRS})
endif()
