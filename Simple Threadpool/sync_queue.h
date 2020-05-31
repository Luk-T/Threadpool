#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>

using std::queue;
using std::mutex;
using std::condition_variable;
using std::unique_lock;
using std::move;

// A thread_safe queue.

// Messages are stored by the FIFO system. A call to receive will
// return the value which has been in the queue for the longest time.
template<class T>
class sync_queue
{
public:
	// Sends a message to the queue. Never blocks.
	void send(const T& value);
	void send(T&& value);

	// Gets a message from the queue. If there are
	// no messages, the thread will be blocked
	T receive();
private:
	queue<T> queue;

	// This mutex locks the queue and prevents double access
	mutex queue_mutex;

	// The condition_variable manages the waiting threads
	condition_variable condition_variable;
};

template<class T>
inline void sync_queue<T>::send(const T& value)
{
	// lock the queue and add a value.
	unique_lock<mutex> lock(queue_mutex);
	queue.push(value);
	lock.unlock();

	// notify one of the threads which is waiting on the
	// condition_variable, if there is one.
	condition_variable.notify_one();
}

template<class T>
inline void sync_queue<T>::send(T&& value)
{
	// lock the queue and add a value.
	unique_lock<mutex> lock(queue_mutex);
	queue.push(move(value));
	lock.unlock();

	// notify one of the threads which is waiting on the
	// condition_variable, if there is one.
	condition_variable.notify_one();
}

template<class T>
inline T sync_queue<T>::receive()
{
	// lock the queue and wait till there is an element in it
	// the mutex will be unlocked while waiting and relocked when resumed
	unique_lock<mutex> lock(queue_mutex);
	while (queue.empty()) {
		condition_variable.wait(lock);
	}

	// return a value from the queue
	T result = move(queue.front());
	queue.pop();
	return result;
}
