#include <iostream>
#include <vector>
#include "accumulate_parallel.h"

using namespace std;


int main()
{
    vector<int> data;
    
    for (int i = 1; i < 1001; ++i) {
        data.push_back(i);
    }
    
    int total = parallel_accumulate(data.begin(), data.end(), 0);
    
    cout << "Sum of numbers from 1 to 1000 are " << total << endl;
    
    return EXIT_SUCCESS;
}
