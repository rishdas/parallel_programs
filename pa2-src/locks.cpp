/* Indiana University
 * School of Informatics and Computing
 * Department of Computer Science
 *
 * Parallelism in Programming Languages and Systems (B524)
 * Spring 2017
 *
 * Programming Assignment 2
 */

/*
 * Includes
 */

// Standard Library Includes

// Local Includes

#include "locks.h"
#include "pa2_atomics.h"

/*
 * Functions
 */

// Dummy Lock

DummyLock::DummyLock(size_t num_threads) {}
void DummyLock::lock(size_t tid)   {}
void DummyLock::unlock(size_t tid) {}

// Standard Wrapper Lock

StdWrapperLock::StdWrapperLock(size_t num_threads) {}

void StdWrapperLock::lock(size_t tid) {
	this->inner_lock.lock();
}

void StdWrapperLock::unlock(size_t tid) {
	this->inner_lock.unlock();
}

bool StdWrapperLock::try_lock(size_t tid) {
	return this->inner_lock.try_lock();
}

// Peterson's Filter Lock

PetersonsFilterLock::PetersonsFilterLock(size_t num_threads) {
	// FIXME
}

void PetersonsFilterLock::lock(size_t tid) {
	// FIXME
}

void PetersonsFilterLock::unlock(size_t tid) {
	// FIXME
}

bool PetersonsFilterLock::try_lock(size_t tid) {
	// FIXME
}

// Bakery Lock

BakeryLock::BakeryLock(size_t num_threads) {
	// FIXME
}

void BakeryLock::lock(size_t tid) {
	// FIXME
}

void BakeryLock::unlock(size_t tid) {
	// FIXME
}

bool BakeryLock::try_lock(size_t tid) {
	// FIXME
}

// Compare-And-Swap Lock

CASLock::CASLock(size_t num_threads) {
	// FIXME
}

void CASLock::lock(size_t tid) {
	// FIXME
}

void CASLock::unlock(size_t tid) {
	// FIXME
}

bool CASLock::try_lock(size_t tid) {
	// FIXME
}

// Test-And-Set Lock

TASLock::TASLock(size_t num_threads) {
	// FIXME
}

void TASLock::lock(size_t tid) {
	// FIXME
}

void TASLock::unlock(size_t tid) {
	// FIXME
}

bool TASLock::try_lock(size_t tid) {
	// FIXME
}

// Test-and-Test-And-Set Lock

TTASLock::TTASLock(size_t num_threads) {
	// FIXME
}

void TTASLock::lock(size_t tid) {
	// FIXME
}

void TTASLock::unlock(size_t tid) {
	// FIXME
}

bool TTASLock::try_lock(size_t tid) {
	// FIXME
}

// Backoff Lock

BackoffLock::BackoffLock(size_t num_threads) {
	// FIXME
}

void BackoffLock::lock(size_t tid) {
	// FIXME
}

void BackoffLock::unlock(size_t tid) {
	// FIXME
}

bool BackoffLock::try_lock(size_t tid) {
	// FIXME
}

// MCS Lock

MCSLock::MCSLock(size_t num_threads) {
	// FIXME
}

void MCSLock::lock(size_t tid) {
	// FIXME
}

void MCSLock::unlock(size_t tid) {
	// FIXME
}

bool MCSLock::try_lock(size_t tid) {
	// FIXME
}
