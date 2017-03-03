#!/usr/bin/sh

# Indiana University
# School of Informatics and Computing
# Department of Computer Science
#
# Parallelism in Programming Languages and Systems (B524)
# Spring 2017
#
# Programming Assignment 1

basedir=$(pwd)

if [ ! -d "./build" ]; then
  mkdir ./build
fi

if [ ! -d "./build/release" ]; then
	echo "Creating Release build directory: ./build/release"
	mkdir ./build/release
	cd ./build/release
	cmake $@ -DCMAKE_BUILD_TYPE=Release ../../
	cd "$basedir"
else
	echo "Release build directory already exists."
fi

echo

if [ ! -d "./build/debug" ]; then
	echo "Creating Debug build directory: ./build/debug"
	mkdir ./build/debug
	cd ./build/debug
	cmake $@ -DCMAKE_BUILD_TYPE=Debug ../../
	cd "$basedir"
else
	echo "Debug build directory already exists."
fi

echo

if [ ! -d "./build/tsan" ]; then
	echo "Creating Thread Sanitizer build directory: ./build/tsan"
	mkdir ./build/tsan
	cd ./build/tsan
	cmake $@ -DCMAKE_BUILD_TYPE=TSan ../../
	cd "$basedir"
else
	echo "Thread Sanitizer build directory already exists."
fi

echo

if [ ! -d "./build/asan" ]; then
	echo "Creating Address Sanitizer build directory: ./build/asan"
	mkdir ./build/asan
	cd ./build/asan
	cmake $@ -DCMAKE_BUILD_TYPE=ASan ../../
	cd "$basedir"
else
	echo "Address Sanitizer build directory already exists."
fi

echo

if [ ! -d "./build/msan" ]; then
	echo "Creating Memory Sanitizer build directory: ./build/msan"
	mkdir ./build/msan
	cd ./build/msan
	cmake -DCMAKE_BUILD_TYPE=MSan ../../
	cd "$basedir"
else
	echo "Memory Sanitizer build directory already exists."
fi

echo

if [ ! -d "./build/usan" ]; then
	echo "Creating Undefined Sanitizer build directory: ./build/usan"
	mkdir ./build/usan
	cd ./build/usan
	cmake $@ -DCMAKE_BUILD_TYPE=Debug ../../
	cd "$basedir"
else
	echo "Undefined Sanitizer build directory already exists."
fi
