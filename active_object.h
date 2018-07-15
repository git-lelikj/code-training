#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

namespace Common
{

template <typename T>
class Concurrent_queue
{
public:
    void enqueue(T t)
    {
        {
            lock_guard<mutex> guard(mutex_);
            queue_.push(move(t));
        }
        queue_empty_.notify_one();
    }

    T dequeue()
    {
        unique_lock<mutex> lock(mutex_);
        queue_empty_.wait(lock, /*!queue_.empty()*/);
        T t = queue_.front();
        queue_.pop();
        return t;
    }

private:
    queue<T> queue_;
    mutable mutex mutex_;
    mutable condition_variable queue_empty_;
};

class Active_object
{

};

}

#endif // ACTIVE_OBJECT_H
