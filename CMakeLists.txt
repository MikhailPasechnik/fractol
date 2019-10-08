cmake_minimum_required(VERSION 3.2)

set(NAME fractol)
project(${NAME} C)
find_package(OpenCL REQUIRED)

add_subdirectory(libft)
file(GLOB SRC src/*.c src/ocl/*.c)
find_package(OpenCL REQUIRED)

link_directories(libft minilibx)
add_executable(${NAME} ${SRC})
target_link_libraries(${NAME} libmlx.a Xext X11 m ft ${OpenCL_LIBRARY})
target_include_directories(${NAME} PUBLIC libft include minilibx ${OpenCL_INCLUDE_DIRS})
