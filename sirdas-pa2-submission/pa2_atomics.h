/* Indiana University
 * School of Informatics and Computing
 * Department of Computer Science
 *
 * Parallelism in Programming Languages and Systems (B524)
 * Spring 2017
 *
 * Programming Assignment 2
 */

#ifndef PA2_ATOMICS_H
#define PA2_ATOMICS_H

/*
 * Includes
 */

// Standard Library includes
#include <utility>

/*
 *  Function Definitions
 */

template <typename... Args>
auto compare_and_swap(Args&&... args) -> decltype(__sync_val_compare_and_swap(std::forward<Args>(args)...)) {
  return __sync_val_compare_and_swap(std::forward<Args>(args)...);
}

template <typename ValType>
ValType test_and_set(ValType* loc) {
	return __sync_lock_test_and_set(loc, 1);
}

template <typename T>
void unset(T* loc) {
	return __sync_lock_release(loc);
}

#endif
