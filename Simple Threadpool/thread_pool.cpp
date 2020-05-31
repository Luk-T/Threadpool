
#include <stdexcept>

#include "thread_pool.h"
#include "thread_pool_internals.h"

using std::invalid_argument;
using std::make_unique;

thread_pool::thread_pool(unsigned int nr_threads) : task_queue(), workers(nr_threads)
{
	if(nr_threads == 0)
		throw invalid_argument("nr_threads must not be 0");

	//create all the workers
	for (unsigned int i = 0; i < nr_threads; i++) {
		workers.push_back(make_unique<worker>(i, task_queue));
	}
}

void thread_pool::execute(task task)
{
	// copy the task to the heap into a unique_ptr
	// and send it into the queue
	task_queue.send(make_unique<::task>(task));
}

thread_pool::~thread_pool()
{
	// Send a nullpointer for every worker.
	// Every worker will pick up a nullpointer from
	// the queue and terminate, so that they can be joined.
	for (unsigned int i = 0; i < workers.size(); i++) {
		task_queue.send(unique_ptr<task>(nullptr));
	}

	// The workers are destructed, the threads are joined automatically
	// once all the tasks are done
}
