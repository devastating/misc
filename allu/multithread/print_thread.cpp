#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <iostream>
#include <pthread.h>

using std::thread;
using std::mutex;
using std::unique_lock;
using std::cout;
using std::flush;
using std::endl;
using std::vector;

typedef bool(*func)(int *cnt);
mutex mtx;

void run_func(int sleep_ms, int increment_cnt, 
                 int *counter, func print_check)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
        unique_lock<mutex> lck(mtx);
        *counter += increment_cnt;
        if (print_check(counter))
        {
            int print_value = *counter;
            lck.unlock();
            cout << "counter: " << print_value << endl << flush;
        }
    }
}

bool thread_a_check(int *cnt)
{
    return (*cnt <= 50);
}

bool thread_c_check(int *cnt)
{
    return (*cnt > 10);
}

bool thread_d_check(int *cnt)
{
    return (*cnt > 30);
}

int main()
{
    //mutex mtx;
    int counter = 0;
    vector<thread *> threads;
    thread *ret;

    // Thread A
    ret = new thread(run_func, 900, 1, &counter, thread_a_check);
    threads.push_back(ret);
    // Thread B
    ret = new thread(run_func, 900, 2, &counter, thread_a_check);
    threads.push_back(ret);
    // Thread C
    ret = new thread(run_func, 900, -1, &counter, thread_c_check);
    threads.push_back(ret);
    // Thread D
    ret = new thread(run_func, 900, -3, &counter, thread_d_check);
    threads.push_back(ret);

    std::this_thread::sleep_for(std::chrono::seconds(3600));
    
    return 0;
}
