cmake_minimum_required(VERSION 3.16)
project(ring_lwe VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_compile_options(-O2)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-g -fsanitize=address,undefined)
  add_link_options(-fsanitize=address,undefined)
endif()

# ── Core library ─────────────────────────────────────────────────────────────
add_library(ring_lwe_lib STATIC
  src/poly.cpp
  src/sampling.cpp
  src/keygen.cpp
  src/encode.cpp
  src/homomorphic.cpp
  src/utils.cpp
)
target_include_directories(ring_lwe_lib PUBLIC include)

# ── CLI executable ────────────────────────────────────────────────────────────
# add_executable(rlwe cli/main_cli.cpp)
# target_link_libraries(rlwe PRIVATE ring_lwe_lib)

# ── Smoke test ────────────────────────────────────────────────────────────────
# add_executable(rlwe_test main.cpp)
# target_link_libraries(rlwe_test PRIVATE ring_lwe_lib)

# ── Benchmark ─────────────────────────────────────────────────────────────────
# add_executable(rlwe_bench bench/benchmark.cpp)
# target_link_libraries(rlwe_bench PRIVATE ring_lwe_lib)

# ── Install ───────────────────────────────────────────────────────────────────
# install(TARGETS rlwe DESTINATION bin)

# ── Main executable ───────────────────────────────────────────────────────────
add_executable(rlwe main.cpp)
target_link_libraries(rlwe PRIVATE ring_lwe_lib)
