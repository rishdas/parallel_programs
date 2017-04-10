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

#include <iostream>

#include "locks.h"
#include "pa2_atomics.h"

/*
 * Static Variables
 */

thread_local QNode* MCSLock::myNode;
using namespace std;
/*
 * Functions
 */

// Dummy Lock

DummyLock::DummyLock(size_t num_threads) {}
void DummyLock::lock(size_t tid)   {}
void DummyLock::unlock(size_t tid) {}
bool DummyLock::try_lock(size_t tid) {
    return true;
}

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
    size_t me = tid;
    for (size_t i = 1; i < num_threads; i++) {
	level[me] = i;
	victim[i] = me;
	while (sameOrHigher(me, i) && victim[i] == me) {
	    return false;
	}
    }
    return true;
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
    size_t i = tid;
    flag[i] = true;
    label[i] = maxLabel() + 1;
    for (size_t k = 0; k < num_threads; k++) {
	while (k != i && (flag[k] && isLabelLessThan(k, i))) {
	    return false;
	}
    }
    return true;
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
    state = 0;
}

void CASLock::lock(size_t tid) {
    while(!(compare_and_swap(&state, 0, 1) == 0));
}

void CASLock::unlock(size_t tid) {
    state = 0;
}

bool CASLock::try_lock(size_t tid) {
    if(compare_and_swap(&state, 0, 1) == 0) {
    	return true;
    }
    return false;
}

// Test-And-Set Lock

TASLock::TASLock(size_t num_threads) {
    state = 0;
}

void TASLock::lock(size_t tid) {
    while(test_and_set<int>(&state));
}

void TASLock::unlock(size_t tid) {
    unset<int>(&state);
}

bool TASLock::try_lock(size_t tid) {
    if (test_and_set<int>(&state)) {
	return false;
    }
    return true;
}

// Test-and-Test-And-Set Lock

TTASLock::TTASLock(size_t num_threads) {
    state = 0;
}

void TTASLock::lock(size_t tid) {
    while(true) {
	while(state != 0);
	if (test_and_set<int>(&state) == 0) {
	    return;
	}
    }
}

void TTASLock::unlock(size_t tid) {
    unset<int>(&state);
}

bool TTASLock::try_lock(size_t tid) {
    if (state == 1) {
	return false;
    }
    return (test_and_set<int>(&state) == 0);
}

// Backoff Lock

BackoffLock::BackoffLock(size_t num_threads) {
    state = 0;
    isFirstTry = true;
}

void BackoffLock::lock(size_t tid) {
    Backoff backoff(MIN_DELAY, MAX_DELAY);
    while(true) {
	while(state != 0);
	if (test_and_set<int>(&state) == 0) {
	    return;
	} else {
	    backoff.doBackoff();
	}
    }
}

void BackoffLock::unlock(size_t tid) {
    unset<int>(&state);
}
//Back off once if lock available initially and TAS fails and then return false
bool BackoffLock::try_lock(size_t tid) {
    Backoff backoff(MIN_DELAY, MAX_DELAY);
    if (state == 1) {
	return false;
    }
    if (test_and_set<int>(&state) == 0) {	
	return true;
    } else if (isFirstTry == false) {
	return false;
    } else {
	isFirstTry = false;
	backoff.doBackoff();
	return this->try_lock(tid);
    }
}

Backoff::Backoff(int min, int max) {
    minDelay = min;
    maxDelay = max;
    srand(time(NULL));
    delay = minDelay + rand()%(maxDelay-minDelay);
}
void Backoff::doBackoff() {
    this_thread::sleep_for(chrono::seconds(delay));
    delay = minDelay + rand()%(maxDelay-minDelay);
}
// MCS Lock

MCSLock::MCSLock(size_t num_threads) {
    tail = NULL;
    myNode = NULL;
}

void MCSLock::lock(size_t tid) {
    if (myNode == NULL) {
	myNode = new QNode();
    }
    QNode *qnode = myNode;
    QNode *pred = __sync_lock_test_and_set(&tail, qnode);

    if (pred != NULL) {
    	qnode->locked = true;
    	pred->next = qnode;

    	while(qnode->locked);
    }
}

void MCSLock::unlock(size_t tid) {
    QNode *qnode = myNode;
    if (qnode->next == NULL) {
    	if (__sync_bool_compare_and_swap(&tail, qnode, nullptr)) {
    	    return;
    	}
    	while (qnode->next == NULL);
    }
    qnode->next->locked = false;
    qnode->next = NULL;
}

bool MCSLock::try_lock(size_t tid) {

    if (myNode == NULL) {
	myNode = new QNode();
    }
    QNode *qnode = myNode;

    if (tail == NULL) {
	if (__sync_bool_compare_and_swap(&tail, NULL, qnode)) {
    	    return true;
    	}
    }
    return false;	
}

QNode::QNode() {
    locked = false;
    next = NULL;
}
