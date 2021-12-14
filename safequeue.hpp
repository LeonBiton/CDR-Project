#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue{
public:
    SafeQueue(size_t a_capacity);
    ~SafeQueue() = default;

    void Push(T& a_data);
    T Pop();
    T Front();
    bool IsEmpty();
    size_t Size();

private:
    std::queue<T> m_safeQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::condition_variable m_condition2;
    size_t m_size;
};

template <typename T>
SafeQueue<T>::SafeQueue(size_t a_capacity)
:m_safeQueue(),
m_size(a_capacity){}

template <typename T>
void SafeQueue<T>::Push(T& a_data){
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_safeQueue.size() == m_size){
        m_condition2.wait(lock);
    }
    m_safeQueue.push(a_data);
    lock.unlock();
    m_condition.notify_all();
}

template <typename T>
T SafeQueue<T>::Pop(){
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_safeQueue.empty()){
        m_condition.wait(lock);
    }
    T returnData = m_safeQueue.front();
    m_safeQueue.pop();
    lock.unlock();
    m_condition2.notify_all();
    return returnData;
}

template <typename T>
bool SafeQueue<T>::IsEmpty(){
    return m_safeQueue.empty();
}

template <typename T>
T SafeQueue<T>::Front(){
    return m_safeQueue[m_safeQueue.front];
}

template <typename T>
size_t SafeQueue<T>::Size(){
    return m_safeQueue.size();
}