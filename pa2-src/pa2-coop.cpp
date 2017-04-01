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

#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>

// Local Includes

#include "locks.h"

using namespace std;

/*
 * Macros
 */

#define HASH_START_STATE 0xcc9e2d51
#define HASH_MAGIC0 0xe6546b64

/*
 * Types
 */

#if PA2_STD_LOCK
typedef StdWrapperLock lock_t;
#elif PA2_PETERSONS_FILTER_LOCK
typedef PetersonsFilterLock lock_t;
#elif PA2_BAKERY_LOCK
typedef BakeryLock lock_t;
#elif PA2_CAS_LOCK
typedef CASLock lock_t;
#elif PA2_TAS_LOCK
typedef TASLock lock_t;
#elif PA2_TTAS_LOCK
typedef TTASLock lock_t;
#elif PA2_BACKOFF_LOCK
typedef BackoffLock lock_t;
#elif PA2_MCS_LOCK
typedef MCSLock lock_t;
#else
typedef DummyLock lock_t;
#endif

/*
 * Forward Declarations
 */

basic_ostream<char>& tout(size_t tid);
void update_hash_state(uint32_t& state, uint32_t data_word);
void worker_fun(size_t tid, lock_t& data_lock);

/*
 * Global Variables
 */

size_t num_threads, data_size;

volatile size_t round_num;

vector<uint32_t> data;

/*
 * Functions
 */

int main(int argc, char** argv) {
	if (argc == 2 and strncmp("-h", argv[1], 2) == 0) {
		cout << "Usage: " << argv[0] << " [num_threads] [num_rounds] [data_size]\n";
		exit(0);
	}

	num_threads = argc >= 2 ? atoi(argv[1]) :               4;
	round_num   = argc >= 3 ? atoi(argv[2]) : num_threads * 4;
	data_size   = argc >= 4 ? atoi(argv[3]) :            1024;

	// Allocate data buffer.
	data.resize(data_size);

	// Reserve space for our vector of thread objects.
	vector<thread> thread_v;
	thread_v.reserve(num_threads);

	// Spawn our threads.
	for (size_t thread_id = num_threads; thread_id-- > 0;) {
		thread_v.emplace_back(worker_fun, thread_id);
	}

	// Join our threads.
	for (thread& t : thread_v) {
		t.join();
	}

	return 0;
}

void worker_fun(size_t tid) {
	tout(tid) << "Entering thread." << endl;

	// Initialize the pseudo-random number generator.
	random_device rd;
	default_random_engine entropy_engine(rd());
	uniform_int_distribution<uint32_t> ui_dist(0, numeric_limits<uint32_t>::max());

	while (round_num > 0) {
		// Initialize the 'hash' states.
		uint32_t old_state = HASH_START_STATE,
		         new_state = HASH_START_STATE;

		// Generate new data and hash as we go
		for (size_t index = data_size; index-- > 0;) {
			uint32_t new_val = ui_dist(entropy_engine);

			update_hash_state(old_state, data[index]);
			update_hash_state(new_state, new_val);

			data[index] = new_val;
		}

		// Print result of hasing the old and new data.
		tout(tid) << "Old data hash: 0x" << hex << setfill('0') << setw(8) << old_state << endl;
		tout(tid) << "New data hash: 0x" << hex << setfill('0') << setw(8) << new_state << endl << endl;

		// Decrement the round count.
		--round_num;
	}
}

void update_hash_state(uint32_t& state, uint32_t data_word) {
	state ^= data_word;

	switch (state % 3) {
	case 0:
		state *= HASH_MAGIC0;
		break;
	case 1:
		state = (state << 8) | (state >> 24);
		break;
	case 2:
		uint8_t rot_size = data_word % 32;
		state ^= (state << rot_size) | (state >> (32 - rot_size));
		break;
	}
}

basic_ostream<char>& tout(size_t tid) {
	return (cout << "[Thread " << dec << tid << "]: ");
}
