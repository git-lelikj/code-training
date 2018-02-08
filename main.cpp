// --------------------------------------------------------------------------------------------------------------------------
// std concurrency samples and solutions
// --------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------------
// simple thread
// --------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <random>

using namespace std;

namespace
{
    class Active
    {
    public:
        void svc()
        {
            default_random_engine dre(555);
            uniform_int_distribution<int> id(3000, 10000);
            cout << "Hi from active object (member): " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(id(dre)));
            cout << "thread " << this_thread::get_id() << " finished" << endl;
        }

        thread activate()
        {
//            thread t(mem_fn(&Active::svc), this);
            thread t(&Active::svc, this);
            return t;
        }
    };
}

int main(int argc, char *argv[])
{
    cout << "Starting new thread, main thread id: " << this_thread::get_id() << endl;

    vector<thread> thread_mgr;

    {
        Active a;
        thread t = a.activate();
        thread_mgr.push_back(move(t));
    }
    {
        Active a;
        thread_mgr.push_back(a.activate());
    }

    for (auto& t: thread_mgr) {
        t.join();
    }

    cout << "Finished\n";

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------------------------------------
// concurrent queue
// --------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

using namespace std;

namespace
{
    template <typename T>
    struct Concurrent_queue
    {
        // pop an element and return a copy. Block if queue empty.
        T dequeue()
        {
            T t;
            {
                unique_lock<mutex> l(mutex_);
                not_empty_cond_.wait(l, [this]{ return !queue_.empty(); });
                t = queue_.front();
                queue_.pop();
            }
            return t;
        }

        //  push an element to the back of the queue.
        void enqueue(const T& item)
        {
            {
                lock_guard<mutex> l(mutex_);
                queue_.push(item);
            }
            not_empty_cond_.notify_one();
        }

        queue<T> queue_;
        mutable mutex mutex_;
        mutable condition_variable not_empty_cond_;
    };

    Concurrent_queue<int> message_q;

    void provider(int val)
    {
        cout << "provider: " << this_thread::get_id() << ", providing: " << val << endl;
        message_q.enqueue(val);
    }

    void consumer()
    {
        int val = message_q.dequeue();
        cout << "consumer: " << this_thread::get_id() << ", consumed: " << val << endl;
    }
}

int main(int argc, char *argv[])
{
    auto p1 = async(launch::async, provider, 55);
    auto p2 = async(launch::async, consumer);

    return 0;
}
#endif

// --------------------------------------------------------------------------------------------------------------------------
// Active Object: draft
// --------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <string>
#include <chrono>
#include <utility>
#include <tuple>

using namespace std;

namespace
{
    template <typename T>
    class Concurrent_queue
    {
    public:
        // pop an element and return a copy. Block if queue empty.
        T dequeue()
        {
            T t;
            {
                unique_lock<mutex> l(mutex_);
                not_empty_cond_.wait(l, [this]{ return !queue_.empty(); });
                t = queue_.front();
                queue_.pop();
            }
            return t;
        }

        //  push an element to the back of the queue.
        void enqueue(const T& item)
        {
            {
                lock_guard<mutex> l(mutex_);
                queue_.push(item);
            }
            not_empty_cond_.notify_one();
        }
    private:
        queue<T> queue_;
        mutable mutex mutex_;
        mutable condition_variable not_empty_cond_;
    };

    class Active_object
    {
    public:
        using Method_request = function<void()>;
        using Activation_queue = Concurrent_queue<Method_request>;

        thread activate()
        {
            thread t([this]{ while(!done) { activation_q_.dequeue()(); } });
            return t;
        }

        void stop()
        {
            activation_q_.enqueue([this]{ done = true; });
        }

        void send(Method_request mr)
        {
            activation_q_.enqueue(mr);
        }
        template <typename F, typename... Args>
        void concurrent_call(F f, Args... args)
        {
#if 0 // supported starting from gcc 4.9
            auto mr = [=]{ f(args...); };
            activation_q_.enqueue(mr);
#endif
//            auto t = make_tuple(args...);
            auto mr = [f, t = make_tuple(args...)]{ };
        }
    private:
        Activation_queue activation_q_;
        bool done = false;
    };

    class Concrete: public Active_object
    {
    public:
        void interface_f(int a, string b, double c)
        {
            this->send([=]{ interface_f_impl(a, b, c); });
#if 0
            this->concurrent_call(interface_f_impl, a, b, c);
#endif

        }

    protected:
        void interface_f_impl(int a, string b, double c)
        {
            cout << "impl: thread: " << this_thread::get_id() << ", prms: " << a << "," << b << "," << c << endl;
        }
    };
}

int main(int argc, char *argv[])
{
    cout << "main thread: " << this_thread::get_id() << ", starting ao...\n";
    Concrete ao;
    thread t = ao.activate();

    ao.interface_f(5, "major Tom", 3.14);
    this_thread::sleep_for(chrono::milliseconds(3000));
    ao.stop();

    t.join();

    return 0;
}
