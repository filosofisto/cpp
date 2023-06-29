#include <iostream>
#include <thread>
#include <vector>
#include "monitor.h"

int main() {
    std::cout << '\n';
    constexpr auto NumberThreads = 100;
    ThreadSafeQueue<int> safeQueue;
    auto addLambda = [&safeQueue](int val) {
        safeQueue.add(val);
        std::cout << val << " " << std::this_thread::get_id() << "; "; 
    };
    auto getLambda = [&safeQueue] { safeQueue.get(); };

    std::vector<std::thread> addThreads(NumberThreads);
    Dice dice;
    for (auto& thr: addThreads) thr = std::thread(addLambda, dice());
    
    std::vector<std::thread> getThreads(NumberThreads);
    for (auto& thr: getThreads) thr = std::thread(getLambda);
    
    for (auto& thr: addThreads) thr.join();
    for (auto& thr: getThreads) thr.join();
    
    std::cout << "\n\n";
    
    return EXIT_SUCCESS;
}
