#ifndef ACCUMULATE_PARALLEL_H
#define ACCUMULATE_PARALLEL_H

#include <thread>
#include <vector>
#include <numeric>

using std::thread;
using std::min;
using std::vector;
using std::advance;
using std::ref;
using std::accumulate;
using std::distance;
using std::cout;
using std::endl;

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = distance(first, last);
    if (!length) return init;
    
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = thread::hardware_concurrency();
    unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length/num_threads;
    
    cout << "max threads:      " << max_threads      << endl;
    cout << "hardware threads: " << hardware_threads << endl;
    cout << "num_threads:      " << num_threads      << endl;
    cout << "block size:       " << block_size       << endl;
    
    vector<T> results(num_threads);
    vector<thread> threads(num_threads-1);
    Iterator block_start = first;
    
    for (size_t i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        advance(block_end, block_size);
        threads[i] = thread(accumulate_block<Iterator, T>(), block_start, block_end, ref(results[i]));
        block_start = block_end;
    }
    
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads-1]);
    
    for(auto& entry: threads) entry.join();
                            
    return accumulate(results.begin(), results.end(), init);
}

#endif
