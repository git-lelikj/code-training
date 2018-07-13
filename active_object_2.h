#ifndef ACTIVE_OBJECT_2_H
#define ACTIVE_OBJECT_2_H

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

using namespace std;

namespace Common
{

template <typename T>
class Concurrent_queue
{
public:
    void enqueue(T t)
    {
        lock_guard<mutex> lock(mutex_);
        queue.push(move(t));
    }

    shared_ptr<T> wait_and_dequeue()
    {
        unique_lock<mutex> lock(mutex_);
        not_empty_cond_.wait(lock, [this](){ return !queue_.empty() });
        shared_ptr<T> res = make_shared<T>()
    }

    void wait_and_dequeue(T& t)
    {

    }

    bool empty()
    {

    }

private:
    queue<T> queue_;
    mutable mutex mutex_;
    mutable condition_variable not_empty_cond_;
};

}

#endif // ACTIVE_OBJECT_2_H
