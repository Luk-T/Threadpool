#include "executors.h"

void multi_threaded::execute(task task)
{
	thread thread(task);
	threads.push_back(std::move(thread));
}

multi_threaded::~multi_threaded()
{
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
}

void single_threaded::execute(task task)
{
	task();
}
