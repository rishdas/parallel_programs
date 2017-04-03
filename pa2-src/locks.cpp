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
    this->level = new size_t[num_threads];
    this->victim = new size_t[num_threads];
    this->num_threads = num_threads;
    for (size_t i = 0; i < num_threads; i++) {
	level[i] = 0;
    }
}

void PetersonsFilterLock::lock(size_t tid) {
    size_t me = tid;
    for (size_t i = 1; i < num_threads; i++) {
	level[me] = i;
	victim[i] = me;
	while (sameOrHigher(me, i) && victim[i] == me);
    }
}

void PetersonsFilterLock::unlock(size_t tid) {
    size_t me = tid;
    level[me] = 0;
}

bool PetersonsFilterLock::try_lock(size_t tid) {
    return true;
	// FIXME
}

bool PetersonsFilterLock::sameOrHigher(size_t me, size_t i) {
    for(size_t k = 0; k < num_threads; k++) {
	if (k != me && level[k] >= i) {
	    return true;
	}
    }
    return false;
}
// Bakery Lock

BakeryLock::BakeryLock(size_t num_threads) {    
    this->flag = new bool[num_threads];
    this->label = new size_t[num_threads];
    this->num_threads = num_threads;
    for (size_t i = 0; i < num_threads; i++) {
	flag[i] = false;
	label[i] = 0;
    }
}

void BakeryLock::lock(size_t tid) {
    size_t i = tid;
    //cout << "Thread ID: " << thread_id<< endl;
    flag[i] = true;
    label[i] = maxLabel() + 1;
    for (size_t k = 0; k < num_threads; k++) {
	while (k != i && (flag[k] && isLabelLessThan(k, i)));
    }
}

void BakeryLock::unlock(size_t tid) {
    flag[tid] = false;
}

bool BakeryLock::try_lock(size_t tid) {
    return true;
	// FIXME
}

size_t BakeryLock::maxLabel() {
    size_t max = 0; //size_t min
    for (size_t i = 0; i < num_threads; i++) {
	if (label[i] > max) {
	    max = label[i];
	}
    }
    return max;
}

bool BakeryLock::isLabelLessThan(size_t k, size_t i) {
    if (label[k] < label[i])
	return true;
    else if (label[k] == label[i] && k<i) {
	return true;
    }
    return false;
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
    return true;
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
    return true;
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
    return true;
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
    return true;
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
    return true;
	// FIXME
}
