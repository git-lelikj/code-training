#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <functional>
#include <thread>
#include <exception>
#include <iostream>

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
        queue_.push(move(t));
        not_empty_condition_.notify_one();
    }

    shared_ptr<T> dequeue()
    {
        unique_lock<mutex> lock(mutex_);
        not_empty_condition_.wait(lock, [this](){ return !queue_.empty(); });
        shared_ptr<T> res = make_shared<T>(move(queue_.front()));
        queue_.pop();
        return res;
    }

    void dequeue(T& t)
    {
        unique_lock<mutex> lock(mutex_);
        not_empty_condition_.wait(lock, [this](){ return !queue_.empty(); });
        t = move(queue_.front());
        queue_.pop();
    }

    bool empty() const
    {
        lock_guard<mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    queue<T> queue_;
    mutable mutex mutex_;
    mutable condition_variable not_empty_condition_;
};

class Active_object
{
public:
    using Method_request = function<void()>;
    using Activation_queue = Concurrent_queue<Method_request>;

    ~Active_object()
    {
//        if (thread_.joinable())
//            thread_.join();
    }

    void send(Method_request mr)
    {
        activation_q_.enqueue(move(mr));
    }

    void activation_queue_loop()
    {
        cout << "[ao]: activation_queue_loop, thread id: " << this_thread::get_id() << endl;
        while (!done_)
        {
            try {
                (*activation_q_.dequeue())();
            }
            catch (const exception& e) {
                cout << "[Active object]: exception cought: " << e.what() << endl;
            }
            catch (...) {
                cout << "[Active object]: exception cought: Unkonwn\n";
            }
        }
    }

    void start()
    {
        cout << "[ao::start]\n";
        thread_ = thread([this](){ cout << "[thread svc]: start...\n"; activation_queue_loop(); });
    }

    void stop()
    {
        this->send([this](){ done_ = true; });
    }

    void wait()
    {
        if (thread_.joinable())
            thread_.join();
    }

    void detach()
    {
        thread_.detach();
    }

private:
    Activation_queue activation_q_;
    thread thread_;
    bool done_ = false;
};

}

#endif // ACTIVE_OBJECT_H
