#pragma once

#include <memory>
#include <thread>

#include "sync_queue.h"
#include "thread_pool.h"

using std::reference_wrapper;
using std::thread;

// A worker of the thread pool.
// Its main job is to take tasks out of the queue
// and execute them in another thread
class worker {
public:
	worker(unsigned int worker_id, sync_queue<unique_ptr<task>>& queue);
	~worker();
private:
	static void do_work(reference_wrapper<sync_queue<unique_ptr<task>>> queue);
	unsigned int worker_id;
	thread thread;
};