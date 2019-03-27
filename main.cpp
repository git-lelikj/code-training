/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;


class Semaphore
{
public:
    explicit Semaphore(size_t c=0):
        count_(c)
    {}
    
    void post()
    {
        lock_guard<mutex> l(m_);
        ++count_;
        cv_.notify_one();
    }
    
    void wait()
    {
        unique_lock<mutex> l(m_);
        cv_.wait(l, [this](){ return count_ > 0; });
        --count_;
    }
    
    template<typename Clock, typename Duration>
    bool wait_until(const chrono::time_point<Clock, Duration>& tp)
    {
        unique_lock<mutex> l(m_);
        if (!cv_.wait_until(l, tp, [this](){ return count_ > 0; }))
            return false;
        else {
            --count_;
            return true;
        }
    }

private:
    mutable mutex m_;
    mutable condition_variable cv_;
    size_t count_ = 0;
};

class Timer_queue
{
public:
protected:
private:
};

int main()
{
    Semaphore s;

    return 0;
}
