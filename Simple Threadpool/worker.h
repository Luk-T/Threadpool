#pragma once

#include <thread>

#include "sync_queue.h"
#include "task.h"

class worker {
public:
	worker(unsigned int worker_id, std::reference_wrapper<sync_queue<message>> queue);
	~worker();
private:
	static void do_work(std::reference_wrapper<sync_queue<message>> queue);
	unsigned int worker_id;
	std::thread thread;
};
