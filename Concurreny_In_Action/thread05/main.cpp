#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>
#include <chrono>
#include <string>

using std::mutex;
using std::queue;
using std::vector;
using std::condition_variable;
using std::lock_guard;
using std::unique_lock;
using std::this_thread::get_id;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::thread;
using std::string;

struct data_chunk
{
    data_chunk(const vector<int>& data): m_data(data) {}
    vector<int> m_data;
};

mutex mut;
queue<data_chunk> data_queue;
condition_variable data_cond;
time_point<high_resolution_clock> start_time;

void show_thread(const string& action)
{
    cout << "Thread " << get_id() << " - action: " << action << endl;
}

bool more_data_to_prepare()
{
    return data_queue.size() < 1000;
}

data_chunk prepare_data()
{
    vector<int> data;
    
    for (int i = 0; i < 500; ++i) {
        data.push_back(i);
    }
    
    return data_chunk{data};
}

void process(const data_chunk& data)
{
    int sum = 0;
    
    for (int value: data.m_data) {
        sum += value;
    }
    
    show_thread("Data processed");
}

void data_preparation_thread()
{
    while (more_data_to_prepare()) {
        const data_chunk data = prepare_data();
        {
            show_thread("try to push data on queue");
            lock_guard<mutex> lk(mut);
            data_queue.push(data);
            show_thread("data pushed on the queue");
        }
        
        data_cond.notify_one();
    }
}

bool is_last_chunk()
{
    auto end_time = high_resolution_clock::now();
    auto time_diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    
    return time_diff_ms > 10*1000;
}

/**
 * 
The implementation of wait() then checks the condition (by calling the supplied lambda function) and returns if it’s satisfied (the lambda function returned true). 
If the condition isn’t satisfied (the lambda function returned false), wait() unlocks the mutex and puts the thread in a blocked or waiting state. When the condition variable is notified by a call to notify_one() from the data-preparation thread, the thread wakes from its slumber (unblocks it), reacquires the lock on the mutex, and checks the condition again, returning from wait() with the mutex still locked if the condition has been satisfied. If the condition hasn’t been satisfied, the thread unlocks the mutex and resumes waiting. This is why you need the std::unique_lock rather than the std::lock_guard—the waiting thread must unlock the mutex while it’s waiting and lock it again afterward, and std::lock_guard doesn’t provide that flexibility. If the mutex remained locked while the thread was sleeping, the data-preparation thread wouldn’t be able to lock the mutex to add an item to the queue, and the waiting thread would never be able to see its condition satisfied.
 */
void data_processing_thread()
{
    while (true) {
        unique_lock<mutex> lk(mut);
        // if lambda is not satisfied thread will be put in blocked or waiting state, and the mutex will be unlocked
        // when condition advise using notify_one thread will be waked up with, reacquire the lock and lambda condition will be tested again, 
        // returning from wait() with the mutex still locked if the condition has been satisfied
        // After consume data (front and pop), thread unlock the mutex and process the data
        data_cond.wait(lk, [] { return !data_queue.empty(); });
        show_thread("Consuming data from queue");
        data_chunk data = data_queue.front();
        data_queue.pop();
        
        lk.unlock();
        process(data);
        if (is_last_chunk()) break;
    }
}

int main()
{
    start_time = high_resolution_clock::now();
    thread t_producer(data_preparation_thread);
    thread t_consumer(data_processing_thread);
    
    t_producer.join();
    t_consumer.join();
    
    return EXIT_SUCCESS;
}
