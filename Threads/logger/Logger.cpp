//
// Created by Eduardo Ribeiro Silva on 06/02/2023.
//

#include <fstream>
#include "Logger.h"

using std::unique_lock;
using std::move;
using std::ofstream;
using std::cerr;
using std::endl;
using std::defer_lock;
using std::queue;

Logger::Logger() {
    m_thread = thread { &Logger::processEntries, this };
}

Logger::~Logger() {
    {
        unique_lock lock { m_mutex };
        // Gracefully shut down the thread by setting m_exit to true
        m_exit = true;
    }
    // Notify condition variable to wake up thread
    m_condVar.notify_all();

    // Wait until thread is shut down. This should be outside the above code
    // block because the lock must be released before calling join()!
    m_thread.join();
}

void Logger::log(string entry) {
    // Lock mutex ad add entry to the queue
    unique_lock lock { m_mutex };
    m_queue.push(move(entry));

    // Notify condition variable to wake up thread
    m_condVar.notify_all();
}

void Logger::processEntries() {
    // Open log file
    ofstream logFile { "log.txt" };
    if (logFile.fail()) {
        cerr << "Failed to open log file." << endl;
    }

    // Create a lock for m_mutex, but do not yet qcquire a lock on it
    unique_lock lock { m_mutex, defer_lock };

    // Start processing loop
    while (true) {
        lock.lock();

        if (!m_exit) {
            // Wait for a notification
            m_condVar.wait(lock);
        } else {
            // We have to exit, process the remaining entries in the queue
            processEntriesHelper(m_queue, logFile);
            break;
        }

        // Condition variable is notified, so something might be in the queue

        // While we still have a lock, swap the contents of the current queue
        // with an empty local queue on the stack
        ::queue<string> localQueue;
        localQueue.swap(m_queue);

        // Now that all entries have been moved from the current queue to the
        // local queue, we can release the lock so other threads are not blocked
        // while we process the entries
        lock.unlock();

        // Process the entries in the local queue on the stack. This happens after
        // having released the lock, so other threads are not blocked anymore
        processEntriesHelper(localQueue, logFile);
    }
}

void Logger::processEntriesHelper(queue<string> &queue, ofstream &out) {
    while (!queue.empty()) {
        out << queue.front() << endl;
        queue.pop();
    }
}
