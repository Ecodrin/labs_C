#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>


template<typename T>
class SafeQueue {
private:
    std::queue<T> data;
    std::mutex mutex;
    std::condition_variable cv;
public:
    SafeQueue() = default;
    ~SafeQueue() = default;
    void push(const T &el);
    void push(T &&el);
    void pop();
    T &top();

    bool empty();
};

template<typename T>
bool SafeQueue<T>::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return data.empty();
}

template<typename T>
T &SafeQueue<T>::top() {
    std::lock_guard<std::mutex> lock(mutex);
    T &el = data.front();
    return el;
}

template<typename T>
void SafeQueue<T>::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !data.empty(); });
    data.pop();
}

template<typename T>
void SafeQueue<T>::push(const T &el) {
    std::lock_guard<std::mutex> lock(mutex);
    data.push(el);
    cv.notify_one();
}

template<typename T>
void SafeQueue<T>::push(T &&el) {
    std::lock_guard<std::mutex> lock(mutex);
    data.push(el);
}

