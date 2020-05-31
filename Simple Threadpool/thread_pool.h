#pragma once

#include <vector>
#include <functional>

#include "sync_queue.h"
#include "executor.h"

using std::unique_ptr;
using std::vector;

class worker;

// The thread_pool provides a group of workers
// which can work on tasks in seperate threads efficiently.
class thread_pool : public executor
{
public:
	// Creates a thread_pool with a given number of threads.
	// throws std::invalid_argument if nr_thread == 0.
	thread_pool(unsigned int nr_threads);

	// Runs a task on the thread_pool
	void execute(task task) override;

	// Destroys the thread_pool. If threads are still running,
	// the destruktor will wait for them.
	~thread_pool() override;
private:
	sync_queue<unique_ptr<task>> task_queue;
	vector<unique_ptr<worker>> workers;
};
