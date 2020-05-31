
#include <iostream>

#include <chrono>
#include "thread_pool.h"
#include "executors.h"

using std::mutex;
using std::cout;
using std::cin;
using std::endl;
using std::this_thread::sleep_for;
using namespace std::chrono;

void thread_pool_example() {
    thread_pool pool(2);
    mutex output_mutex;

    for (int i = 0; i < 6; i++) {
        // create a closure that should be run on the thread_pool
        auto task = [i, &output_mutex] {
            output_mutex.lock();
            cout << "task " << i << " started" << endl;
            output_mutex.unlock();

            sleep_for(milliseconds(250));

            output_mutex.lock();
            cout << "task " << i << " ended" << endl;
            output_mutex.unlock();
        };

        // execute it
        pool.execute(task);
    }

    // wait for user input to keep the console open
    cin.get();

    // if the thread_pool has not finished here, it will
    // wait automatically for all the threads to finish
}

void get_time(void func()) {
    auto start = high_resolution_clock::now();

    func();

    auto end = high_resolution_clock::now();
    duration<double, std::milli> duration = end - start;


    cout << "Dauer ms: " << duration.count();

    cin.get();
}


void executor_bench() {
    const int repetitions = 5000;
    const int i_max = 1000000;

    //single_threaded executor;
    multi_threaded executor;
    //thread_pool executor(8);

    auto func = [=]() {
        for (int i = 0; i < i_max; i++) {

        }
    };

    for (int i = 0; i < repetitions; i++) {
        executor.execute(func);
    }
}

int main()
{
    thread_pool_example();
    //get_time(executor_bench);

    return EXIT_SUCCESS;
}

