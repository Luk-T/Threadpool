#pragma once

#include <functional>
#include <thread>
#include <vector>

#include "executor.h"

using std::vector;
using std::thread;

class single_threaded : public executor
{
public:
	void execute(task task) override;
};

class multi_threaded : public executor
{
public:
	void execute(task task) override;
	~multi_threaded() override;
private:
	vector<thread> threads;
};