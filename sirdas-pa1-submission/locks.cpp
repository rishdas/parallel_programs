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
#include <iostream>

using namespace std;

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
    this->level = new size_t[num_threads];
    this->victim = new size_t[num_threads];
    this->num_threads = num_threads;
    for (size_t i = 0; i < num_threads; i++) {
	level[i] = 0;
    }
}

void PetersonsFilterLock::lock(void) {
    size_t me = thread_id;
    for (size_t i = 1; i < num_threads; i++) {
	level[me] = i;
	victim[i] = me;
	while (sameOrHigher(me, i) && victim[i] == me);
    }
}

void PetersonsFilterLock::unlock(void) {
    size_t me = thread_id;
    level[me] = 0;
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

void BakeryLock::lock(void) {
    size_t i = thread_id;
    //cout << "Thread ID: " << thread_id<< endl;
    flag[i] = true;
    label[i] = maxLabel() + 1;
    for (size_t k = 0; k < num_threads; k++) {
	while (k != i && (flag[k] && isLabelLessThan(k, i)));
    }

}

void BakeryLock::unlock(void) {
    flag[thread_id] = false;
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
