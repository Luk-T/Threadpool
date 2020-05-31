#include "thread_pool_internals.h"

worker::worker(unsigned int worker_id, sync_queue<unique_ptr<task>>& queue)
{
	this->worker_id = worker_id;
	// Start the thread
	this->thread = std::thread(do_work, std::ref(queue));
}

worker::~worker()
{
	// Join the threads
	thread.join();
}

void worker::do_work(reference_wrapper<sync_queue<unique_ptr<task>>> queue) {
	while (true) {
		auto task = queue.get().receive();

		if (task) {
			try {
				// call the function
				(*task)();
			}
			catch(...) {
				// Write the exception in a logger
			}
		}
		else
		{
			// task was a nullpointer, this is the signal for the thread to stop
			break;
		}
	}
}
