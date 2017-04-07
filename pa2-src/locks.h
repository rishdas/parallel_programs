/* Indiana University
 * School of Informatics and Computing
 * Department of Computer Science
 *
 * Parallelism in Programming Languages and Systems (B524)
 * Spring 2017
 *
 * Programming Assignment 2
 */

#ifndef PA2_LOCKS_H
#define PA2_LOCKS_H

/*
 * Includes
 */

// Standard Library Includes
#include <cstddef>
#include <mutex>

#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <atomic>

#define MIN_DELAY 1
#define MAX_DELAY 5

using namespace std;

struct DummyLock {
	DummyLock(size_t num_threads);

	void lock(size_t tid);
	void unlock(size_t tid);
	bool try_lock(size_t tid);
};

class StdWrapperLock {
	std::mutex inner_lock;

	public:
	StdWrapperLock(size_t num_threads);

	void lock(size_t tid);
	void unlock(size_t tid);
	bool try_lock(size_t tid);
};

class PetersonsFilterLock {
private:
    size_t *level;
    size_t *victim;
    size_t num_threads;
    
public:
    PetersonsFilterLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
    bool sameOrHigher(size_t, size_t);

};

class BakeryLock {
private:
    bool   *flag;
    size_t *label;
    size_t num_threads;
public:
    BakeryLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
    size_t maxLabel();
    bool   isLabelLessThan(size_t, size_t);
};

class CASLock {
    int state;

public:
    CASLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
};

class TASLock {
    int state;

public:
    TASLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
};

class TTASLock {
    int state;

public:
    TTASLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
};

class Backoff {
    int minDelay, maxDelay;
    int       delay;
public:
    Backoff(int min, int max);

    void doBackoff();
};

class BackoffLock {
    int state;
    int isFirstTry;

public:
    BackoffLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
};

class QNode {
public:
    bool  locked;
    QNode *next;
    
    QNode();
    
};
    
class MCSLock {
    atomic<QNode*> tail;
    thread_local static QNode* myNode;

public:
    MCSLock(size_t num_threads);

    void lock(size_t tid);
    void unlock(size_t tid);
    bool try_lock(size_t tid);
};

#endif
