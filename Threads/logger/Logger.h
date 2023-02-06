//
// Created by Eduardo Ribeiro Silva on 06/02/2023.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string>
#include <queue>
#include <iostream>
#include <thread>

using std::string;
using std::queue;
using std::ofstream;
using std::mutex;
using std::condition_variable;
using std::thread;

class Logger {
public:
    Logger();
    Logger(const Logger& src) = delete;
    virtual ~Logger();

    Logger& operator=(const Logger& rhs) = delete;

    void log(string entry);
private:
    void processEntries();
    void processEntriesHelper(queue<string>& queue, ofstream& out);

    mutex m_mutex;
    condition_variable m_condVar;
    queue<string> m_queue;
    thread m_thread;

    // Boolean telling the background thread to terminate
    bool m_exit { false };
};


#endif //LOGGER_LOGGER_H
