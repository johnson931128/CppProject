cmake_minimum_required(VERSION 3.16)
project(HollowClone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入 FetchContent 模組
include(FetchContent)

# 宣告要從 GitHub 下載 SFML 3.0.0
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
)
# 執行下載並將其加入建置目標
FetchContent_MakeAvailable(SFML)

include_directories(include)

add_executable(HollowClone src/main.cpp)

# 連結 SFML 函式庫 (SFML 3.0 依然是這個名稱)
target_link_libraries(HollowClone PRIVATE SFML::Graphics SFML::Window SFML::System)
