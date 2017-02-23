/* Indiana University
 * School of Informatics and Computing
 * Department of Computer Science
 *
 * Parallelism in Programming Languages and Systems (B524)
 * Spring 2017
 *
 * Programming Assignment 1
 */

/*
 * Includes
 */

// Standard Library Includes

// Local Includes

#include "locks.h"

/*
 * Functions
 */

// DummyLock

DummyLock::DummyLock(size_t num_threads) {}
void DummyLock::lock(void)   {}
void DummyLock::unlock(void) {}

// Standard Wrapper Lock

StdWrapperLock::StdWrapperLock(size_t num_threads) {}

void StdWrapperLock::lock(void) {
	this->inner_lock.lock();
}

void StdWrapperLock::unlock(void) {
	this->inner_lock.unlock();
}

// Peterson's Filter Lock

PetersonsFilterLock::PetersonsFilterLock(size_t num_threads) {
	// FIXME
}

void PetersonsFilterLock::lock(void) {
	// FIXME
}

void PetersonsFilterLock::unlock(void) {
	// FIXME
}

// Bakery Lock

BakeryLock::BakeryLock(size_t num_threads) {
	// FIXME
}

void BakeryLock::lock(void) {
	// FIXME
}

void BakeryLock::unlock(void) {
	// FIXME
}
