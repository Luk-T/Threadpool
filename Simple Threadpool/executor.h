#pragma once

#include <functional>

using task = std::function<void()>;

class executor {
public:
	virtual void execute(task) = 0;
	virtual ~executor() = default;
};