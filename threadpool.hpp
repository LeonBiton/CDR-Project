#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__
#include <iostream>
#include <vector>
#include "threadwrapper.hpp"
#include "safequeue.hpp"


class ICommand{
public:
    ICommand() = default;
    virtual void Execute() = 0;
    virtual ~ICommand() = default;
};

class ThreadPool{
public:
    ThreadPool(size_t queueSize , int numOfThreads);
    ~ThreadPool();

    void AddTask(ICommand * a_task);
    void RemoveTask();

private:
    std::vector<Thread> m_workers;
    SafeQueue<ICommand *> m_tasks;
};

#endif