cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
project(ydb-hashtables-bench)

# abseil-cpp
add_subdirectory(vendor/abseil-cpp)

# google sparsehash
add_library(sparsehash INTERFACE)
target_include_directories(sparsehash SYSTEM BEFORE INTERFACE "${PROJECT_SOURCE_DIR}/vendor/sparsehash")

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} absl::flat_hash_map sparsehash)
