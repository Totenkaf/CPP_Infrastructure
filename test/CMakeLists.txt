# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================

cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 20)
# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Includes
# ------------------------------------------------------------------------------
find_package(GTest REQUIRED)

include_directories(${INCLUDES})
set(program_options_src ${PROJECT_SOURCE_DIR}/program_options_unit_test.cpp)

# ------------------------------------------------------------------------------
# 2 | Executables
# ------------------------------------------------------------------------------4
add_executable(po_test ${program_options_src})
target_include_directories(po_test PUBLIC ${LIB_INCLUDE_DIRS})


option(BUILD_DYNAMIC "USING SHARED LIBRARY" OFF) # By default PARALLEL is OFF.
if(BUILD_DYNAMIC)
    target_link_libraries(po_test PUBLIC ${DYNAMIC_LIB} ${GTEST_LIBRARIES} -pthread)
else()
    target_link_libraries(po_test PUBLIC ${STATIC_LIB} ${GTEST_LIBRARIES} -pthread)
endif()


# ==============================================================================
# III | Check settings
# ==============================================================================
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov")
endif()
