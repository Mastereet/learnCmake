# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(DynamicArrayProject VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置项目版本（可选）
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# 包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # 如果有其他包含目录，可以在这里添加，例如：
    # ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
)

# 添加库（如果需要将 Array 和 DynamicArray 编译为库）
add_library(dynamic_array_lib STATIC
    src/Array.cpp
    src/DynamicArray.cpp
)

target_include_directories(dynamic_array_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加主程序
add_executable(main
    src/main.cpp
    # 其他主程序源文件，例如 main.cpp
)

# 链接库到主程序
target_link_libraries(main PRIVATE
    dynamic_array_lib
    # 其他依赖的库，例如：
    # pthread
)

# 如果需要启用测试，可以使用以下命令
enable_testing()

# 添加测试可执行文件
add_executable(dynamic_array_test
    test/main_test.cpp
    # 其他测试源文件，例如 Array_test.cpp, DynamicArray_test.cpp 等
)

# 链接库到测试可执行文件
target_link_libraries(dynamic_array_test PRIVATE
    dynamic_array_lib
    # 其他依赖的库，例如：
    # gtest
)

# 添加测试到 CTest
add_test(
    NAME dynamic_array_test
    COMMAND $<TARGET_FILE:dynamic_array_test>
)

# 可选：安装规则
# install(TARGETS dynamic_array_lib main DESTINATION lib)
# install(FILES include/Array.hpp include/DynamicArray.hpp DESTINATION include)