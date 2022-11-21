#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>


namespace hardmon
{

/*!
 * \brief The CSignalHandler class allows waiting for system signals.
 *
 * The following signals are being handled: SIGTERM, SIGINT, SIGHUP.
 */
class CSignalHandler
{
public:
    CSignalHandler();
    ~CSignalHandler();

    /*!
     * \brief Waits for any of the handled signals.
     */
    void wait();

private:
    static void handler(int signal);

private:
    std::vector<int> m_signals;
    std::condition_variable m_cv;
    std::mutex m_mutex;
};

}
