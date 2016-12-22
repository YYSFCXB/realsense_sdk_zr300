option(BUILD_PKG_CONFIG "set BUILD_PKG_CONFIG to ON if pkg-config tool should be built, set to OFF to skip it" OFF)
if(BUILD_PKG_CONFIG)
    include(cmake_includes/pkg_config)
endif(BUILD_PKG_CONFIG)


set(COMPILE_DEFINITIONS -Wall -Wno-write-strings -Wno-comment -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-variable -Wno-reorder -Werror)
set(PTHREAD pthread)
set(DL dl)
set(GLFW_LIBS glfw)
set(OPENGL_LIBS GL)
set(GTEST_LIBS gtest gtest_main)
set(LZ4 lz4)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 ")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wformat -Wformat-security")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wconversion")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -z noexecstack")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -z relro -z now")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -pie")

set(SAMPLES_TIME_SYNC_TESTS samples_time_sync_tests.cpp)
set(FIND_DATA_PATH_TEST find_data_path_test.cpp)
set(PIPELINE_TEST pipeline_tests.cpp)
