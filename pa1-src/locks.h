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

extern thread_local size_t thread_id;

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
private:
    size_t *level;
    size_t *victim;
    size_t num_threads;
    
public:
    PetersonsFilterLock(size_t num_threads);

    void lock(void);
    void unlock(void);
    bool sameOrHigher(size_t, size_t);
};

class BakeryLock {
private:
    bool   *flag;
    size_t *label;
    size_t num_threads;

public:
    BakeryLock(size_t num_threads);

    void   lock(void);
    void   unlock(void);
    size_t maxLabel();
    bool   isLabelLessThan(size_t, size_t);
};

#endif
