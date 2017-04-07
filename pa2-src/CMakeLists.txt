# Indiana University
# School of Informatics and Computing
# Department of Computer Science
#
# Parallelism in Programming Languages and Systems (B524)
# Spring 2017
#
# Programming Assignment 2

#########################
# Project Configuration #
#########################

cmake_minimum_required(VERSION 3.0.2)
project("Programming Assignment 2" C CXX)

######################
# Tool Configuration #
######################

find_program(CLANG_FORMAT clang-format)

###########################
# Directory Configuration #
###########################

include_directories(${PROJECT_SOURCE_DIR})

##########################
# Compiler Configuration #
##########################

set(CMAKE_POSITION_INDEPENDENT_CODE true)

# Set the C++ standard to C++14.
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")

	# Add the ASan build type.
	set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
	    "Flags used by the C++ compiler during an Address Sanitizer build."
	    FORCE)

	# Add the MSan build type.
	set(CMAKE_CXX_FLAGS_MSAN "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=memory" CACHE STRING
	    "Flags used by the C++ compiler during a Memory Sanitizer build."
	    FORCE)

	# Add the TSan build type.
	set(CMAKE_CXX_FLAGS_TSAN "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=thread" CACHE STRING
	    "Flags used by the C++ compiler during a Thread Sanitizer build."
	    FORCE)

	# Add the USan build type.
	set(CMAKE_CXX_FLAGS_USAN "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined" CACHE STRING
	    "Flags used by the C++ compiler during an Undefined Behaviour Sanitizer build."
	    FORCE)
endif()

############################
# Build Type Configuration #
############################

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
	set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel ASan MSan TSan USan."
		FORCE)
endif()

#################
# Build Targets #
#################

# Busy waiting versions

add_executable(pa2-busy-dummy pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-dummy PRIVATE PA2_DUMMY_LOCK)

add_executable(pa2-busy-std pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-std PRIVATE PA2_STD_LOCK)

add_executable(pa2-busy-petersons pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-petersons PRIVATE PA2_PETERSONS_FILTER_LOCK)

add_executable(pa2-busy-bakery pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-bakery PRIVATE PA2_BAKERY_LOCK)

add_executable(pa2-busy-cas pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-cas PRIVATE PA2_CAS_LOCK)

add_executable(pa2-busy-tas pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-tas PRIVATE PA2_TAS_LOCK)

add_executable(pa2-busy-ttas pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-ttas PRIVATE PA2_TTAS_LOCK)

add_executable(pa2-busy-backoff pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-backoff PRIVATE PA2_BACKOFF_LOCK)

add_executable(pa2-busy-mcs pa2-busy.cpp locks.cpp)
target_compile_definitions(pa2-busy-mcs PRIVATE PA2_MCS_LOCK)

# Cooperatively scheduled versions

add_executable(pa2-coop-dummy pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-busy-dummy PRIVATE PA2_DUMMY_LOCK)

add_executable(pa2-coop-std pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-std PRIVATE PA2_STD_LOCK)

add_executable(pa2-coop-petersons pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-petersons PRIVATE PA2_PETERSONS_FILTER_LOCK)

add_executable(pa2-coop-bakery pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-bakery PRIVATE PA2_BAKERY_LOCK)

add_executable(pa2-coop-cas pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-cas PRIVATE PA2_CAS_LOCK)

add_executable(pa2-coop-tas pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-tas PRIVATE PA2_TAS_LOCK)

add_executable(pa2-coop-ttas pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-ttas PRIVATE PA2_TTAS_LOCK)

add_executable(pa2-coop-backoff pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-backoff PRIVATE PA2_BACKOFF_LOCK)

add_executable(pa2-coop-mcs pa2-coop.cpp locks.cpp)
target_compile_definitions(pa2-coop-mcs PRIVATE PA2_MCS_LOCK)

#########################
# Utility Build Targets #
#########################

if (CLANG_FORMAT)
	add_custom_target(format
		              ${CLANG_FORMAT} -i -sort-includes -style=file locks.cpp locks.h pa2_atomics.h pa2-busy.cpp pa2-coop.cpp)
endif()
