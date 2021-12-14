#include "threadpool.hpp"

void* RunThread(void* a_paremeter);

ThreadPool::ThreadPool(size_t queueSize , int numOfThreads)
:m_tasks(queueSize),
m_workers(){
    for(int i = 0 ; i<numOfThreads ; ++i){
        Thread thread(RunThread , (void *)& m_tasks);
        m_workers.push_back(thread);
    }
}

ThreadPool::~ThreadPool(){
    std::vector<Thread>::iterator it = m_workers.begin();
    while(it != m_workers.end()){
        (*it).Join();
        ++it;
    }
}

void* RunThread(void* a_paremeter) {
    SafeQueue<ICommand*>* queue = reinterpret_cast<SafeQueue<ICommand*>*>(a_paremeter);
    while(1) {
        ICommand* task = queue->Pop();
        task->Execute();
    }
}

void ThreadPool::AddTask(ICommand * a_task){
    //printf("in add\n");
    m_tasks.Push(a_task);
}

void ThreadPool::RemoveTask(){
    m_tasks.Pop();
}
