#include "hardmon/CSignalHandler.hpp"

#include <csignal>
#include <iostream>

namespace hardmon
{

static CSignalHandler* g_signalHandler = nullptr;

CSignalHandler::CSignalHandler()
{
    g_signalHandler = this;

    m_signals.push_back(SIGINT);
    m_signals.push_back(SIGTERM);
    m_signals.push_back(SIGHUP);

    for (int signal : std::as_const(m_signals)) {
        std::signal(signal, CSignalHandler::handler);
    }
}

CSignalHandler::~CSignalHandler()
{
    for (int signal : std::as_const(m_signals)) {
        std::signal(signal, SIG_DFL);
    }

    g_signalHandler = nullptr;
}

void CSignalHandler::wait()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock);
}

void CSignalHandler::handler(int signal)
{
    std::cout << "Signal received, exiting: " << signal << std::endl;

    std::lock_guard<std::mutex> guard(g_signalHandler->m_mutex);
    g_signalHandler->m_cv.notify_all();
}

}
