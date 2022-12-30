# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.8)
project(program_options_lib)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
file(GLOB SOURCES *.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# ------------------------------------------------------------------------------
# 2 | Libs
# ------------------------------------------------------------------------------


option(BUILD_DYNAMIC "USING SHARED LIBRARY" OFF) # By default DYNAMIC is OFF.
if(BUILD_DYNAMIC)
    add_library(${PROJECT_NAME}_dynamic SHARED ${SOURCES})
    set(LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
    set(DYNAMIC_LIB ${PROJECT_NAME}_dynamic PARENT_SCOPE)
else()
    add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
    set(LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
    set(STATIC_LIB ${PROJECT_NAME}_static PARENT_SCOPE)
endif()


# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()
