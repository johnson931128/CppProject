cmake_minimum_required(VERSION 3.10)

# 專案名稱
project(CppReview_Beginning)

# 設定 C++ 標準為 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 開啟所有警告 (Wall) 與額外警告 (Wextra)，這對學習很重要
add_compile_options(-Wall -Wextra)

# --- 定義執行檔 (Executable) ---
# 語法：add_executable(執行檔名稱 原始碼檔案.cpp)

# 1-01
add_executable(env_test 01_env_test.cpp)

# 1-02
add_executable(var_memory 02_var_memory.cpp)

# 1-03
add_executable(scope_life 03_scope_lifetime.cpp)


# 1-04
add_executable(flow_control 04_flow_control.cpp)

# 1-05
add_executable(stack_cost 05_stack_cost.cpp)

# 1-06
add_executable(pointer_test 06_pointer_intro.cpp)

# 1-07
add_executable(pointer_arithmetic 07_pointer_arithmetic.cpp)

# 1-08
add_executable(reference_test 08_reference.cpp)

# 1-09
add_executable(const_pointer 09_const_pointer.cpp)

# 1-10
add_executable(array_string 10_array_string.cpp)

# 1-11
add_executable(big_o_intro 11_big_o_intro.cpp)

# 1-12
add_executable(search_algos 12_search_algos.cpp)















