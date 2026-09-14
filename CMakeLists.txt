cmake_minimum_required(VERSION 4.4.0)

project(raylibproject VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include(FetchContent)

FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/6.0.zip"
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    raylib-cpp
    URL "https://github.com/robloach/raylib-cpp/archive/v6.0.3.zip"
)
option(BUILD_RAYLIB_CPP_MODULES "Build C++ modules support" ON)
FetchContent_MakeAvailable(raylib-cpp)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

add_library(game_logic STATIC ${SOURCES})
target_include_directories(game_logic PUBLIC ${INCLUDE_DIR} ${raylib-cpp_SOURCE_DIR}/include)
target_link_libraries(game_logic PUBLIC
    raylib
)
add_executable(${PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    game_logic
    raylib
)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glu32 winmm gdi32 )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(game_logic copy_assets)

# enable_testing()
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
#     add_subdirectory(tests)
# endif()