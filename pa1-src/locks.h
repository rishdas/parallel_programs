/* Indiana University
 * School of Informatics and Computing
 * Department of Computer Science
 *
 * Parallelism in Programming Languages and Systems (B524)
 * Spring 2017
 *
 * Programming Assignment 1
 */

#ifndef PA1_LOCKS_H
#define PA1_LOCKS_H

#include <cstddef>
#include <mutex>

struct DummyLock {
	DummyLock(size_t num_threads);

	void lock(void);
	void unlock(void);
};

class StdWrapperLock {
	std::mutex inner_lock;

	public:
	StdWrapperLock(size_t num_threads);

	void lock(void);
	void unlock(void);
};

class PetersonsFilterLock {
	// FIXME: Add member variables here.

	public:
	PetersonsFilterLock(size_t num_threads);

	void lock(void);
	void unlock(void);
};

class BakeryLock {
	// FIXME: Add member variables here.

	public:
	BakeryLock(size_t num_threads);

	void lock(void);
	void unlock(void);
};

#endif
