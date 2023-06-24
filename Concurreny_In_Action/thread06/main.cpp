#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::thread;
using std::future;
using std::min;
using std::async;

struct FinalResult
{
    long total;
};

struct ChunkResult
{
    long total;
};

class Data
{
public:
    Data() {}
    void add(int i) { items.push_back(i); }
private:
    vector<int> items;
};

future<FinalResult> process_data(vector<Data>& vec)
{
    const size_t chunk_size = 10;
    vector<future<ChunkResult>> results;
    
    for(auto beg = vec.begin(), end = vec.end(); beg != end;) {
        const size_t remaining_size = end - begin;
        const size_t this_chunk_size = min(remaining_size, chunk_size);
        results.push_back(
            async(process_chunk, beg, beg+this_chunk_size)
        );
        beg += this_chunk_size;
    }
}

int main()
{
    // produce all data to be processed
    Data data;
    for (int i = 1; i < 10'000'000; ++i) 
        data.add(i);
    
    
    
    return EXIT_SUCCESS;
}
