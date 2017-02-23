# Indiana University
# School of Informatics and Computing
# Department of Computer Science
#
# Parallelism in Programming Languages and Systems (B524)
# Spring 2017
#
# Programming Assignment 1

#########################
# Project Configuration #
#########################

cmake_minimum_required(VERSION 3.0.2)
project("Programming Assignment 1" C CXX)

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

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
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

add_executable(pa1-dummy pa1.cpp locks.cpp)
target_compile_definitions(pa1-dummy PRIVATE PA1_DUMMY_LOCK)

add_executable(pa1-std pa1.cpp locks.cpp)
target_compile_definitions(pa1-std PRIVATE PA1_STD_LOCK)

add_executable(pa1-petersons pa1.cpp locks.cpp)
target_compile_definitions(pa1-petersons PRIVATE PA1_PETERSONS_FILTER_LOCK)

add_executable(pa1-bakery pa1.cpp locks.cpp)
target_compile_definitions(pa1-bakery PRIVATE PA1_BAKERY_LOCK)

#########################
# Utility Build Targets #
#########################

if (CLANG_FORMAT)
	add_custom_target(format
		              ${CLANG_FORMAT} -i -sort-includes -style=file locks.cpp locks.h pa1.cpp)
endif()
