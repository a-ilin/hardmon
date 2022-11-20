#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>


namespace hardmon
{

class CSignalHandler
{
public:
    CSignalHandler();
    ~CSignalHandler();

    void wait();

private:
    static void handler(int signal);

private:
    std::vector<int> m_signals;
    std::condition_variable m_cv;
    std::mutex m_mutex;
};

}
