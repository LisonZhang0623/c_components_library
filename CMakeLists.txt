cmake_minimum_required(VERSION 3.10)
project(C_COMPONENTS_LIBRARY)

# C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 头文件全局包含（所有子模块都能找到）
include_directories(
    ${CMAKE_SOURCE_DIR}/components/**/include
)

add_subdirectory(components/Array)
add_subdirectory(components/Vector)

# add_subdirectory(components/jsonParser)

# 主程序
add_executable(${PROJECT_NAME} main.c)

# file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# 链接两个模块库
target_link_libraries(${PROJECT_NAME}
    Array
    Vector
    # jsonParser
)
