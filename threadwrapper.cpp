#include "threadwrapper.hpp"

//------------Thread------------
Thread::Thread(void * a_func(void *) , void * a_parameter) //TODO: throw exepctions
:m_thread(){
    pthread_create(&m_thread ,NULL ,a_func, a_parameter);
}

void Thread::Join(){
    pthread_join(m_thread,NULL);
}


//------------Mutex------------
Mutex::Mutex()
:m_mutex(PTHREAD_MUTEX_INITIALIZER){}

Mutex::~Mutex(){ //TODO: check if it is unlock first
    pthread_mutex_destroy(&m_mutex); 
}

void Mutex::Lock(){
    pthread_mutex_lock(&m_mutex);
}

void Mutex::Unlock(){
    pthread_mutex_unlock(&m_mutex);
}

//------------Semaphore------------

Semaphore::Semaphore(int a_pshared , unsigned int a_semVal){
    sem_init(&m_semaphore , a_pshared , a_semVal);
}

Semaphore::~Semaphore(){
    sem_destroy(&m_semaphore);
}

int Semaphore::Wait(){
    return sem_wait(&m_semaphore);
}

int Semaphore::Post(){
    return sem_post(&m_semaphore);
}

int Semaphore::GetValue(int * a_sval){
    return sem_getvalue(&m_semaphore , a_sval);
}

//------------MySemaphore------------

void MySemaphore::Post(){
    m_mutex.Lock();
    ++m_count;
    m_condition.notify_one();
    m_mutex.Unlock();
}

void MySemaphore::Wait(){
    m_mutex.Lock();
    while(m_count == 0){
       //m_condition.wait(m_mutex);
    }
    --m_count;
    m_mutex.Unlock();
}