#include <iostream>
#include <pthread.h> //for threads
#include <stdio.h>
#include <semaphore.h>
#include <condition_variable>

class Thread{
public:
    Thread(void * a_func(void *) , void * a_parameter);
    ~Thread() = default;

    void Join();

private:
    pthread_t m_thread;
};


class Mutex{
public:
    Mutex();
    ~Mutex();

    void Lock();
    void Unlock();

private:
    pthread_mutex_t m_mutex;

};

class Semaphore{
public:
    Semaphore(int a_pshared , unsigned int a_semVal);
    ~Semaphore();

    int Wait();
    int Post();
    int GetValue(int * a_sval);

private:
    sem_t m_semaphore;

};

class Guard{
public:
    Guard(Mutex& a_mutex): m_mutex(a_mutex){
    m_mutex.Lock();
    }
    ~Guard(){
    m_mutex.Unlock();
    }

private:
    Mutex& m_mutex;

};

class MySemaphore{
public:
    MySemaphore(int a_count): m_count(a_count){}

    void Post();
    void Wait();

private:
    int m_count;
    Mutex m_mutex;
    std::condition_variable m_condition;
};


