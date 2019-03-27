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
    using Timeout_handler = function<void()>;
    using Clock = chrono::steady_clock;
    using Clock_tp = chrono::steady_clock::time_point;
    using Timer_id = uint64_t;

    Timer_queue() = default;
    
    void run()
    {
        while (!done_) {
            auto wt = this->get_earliest_wait_time();
            if (wt.first) {
                timers_sem_.wait_until(wt.second);
            }
            else {
                timers_sem_.wait();
            }
            this->process_timers();
        }
        cout << "[run]: done, exiting\n";
    }
    
    void stop()
    {
        schedule_timer([this]{ done_ = true; }, 0);
    }
    
    Timer_id schedule_timer(Timeout_handler th, int64_t interval, int64_t period=0)
    {
        auto id = generate_unique_id();
        Timer t(move(th), id, period);
        {
            lock_guard<mutex> l(mutex_);
            // insert to list of timers_sem_
            timers_.push_front(move(t));
            // add to hash of ids
            timer_id_hash_.insert({id, timers_.begin()});
            // add to timers heap
            timer_heap_.push(Timer_slot{Clock::now()+chrono::milliseconds(interval), timers_.begin()});
        }
        timers_sem_.post();        
        return id;
    }
    
    bool cancel_timer(Timer_id id)
    {
        {
            lock_guard<mutex> l(mutex_);
            auto it = timer_id_hash_.find(id);
            if (it != timer_id_hash_.end()) {
                (*it->second).cancel();
                cout << "[cancel_timer]: timer found: id: " << (*it->second).id_ << ", cancelled: " << (*it->second).cancelled_ << endl;
                return true;
            }
            else {
                //TBD
                cout << "[cancel_timer]: timer not found: " << id << endl;
                return false;
            }
        }
        timers_sem_.post();        
    }
    
    size_t num_timers() const { return timers_.size(); }
    
protected:

    pair<bool, Clock_tp> get_earliest_wait_time()
    {
        lock_guard<mutex> l(mutex_);
        while (timer_heap_.size()) {
            auto timer_it = timer_heap_.top().timer_it_;
            if (!timer_it->cancelled_) {
                return {true, timer_heap_.top().end_};
            }
            else {
                // cancelled timer, remove from all structures
                auto hash_it = timer_id_hash_.find(timer_it->id_);
                if (hash_it != timer_id_hash_.end())
                    timer_id_hash_.erase(hash_it);
                timers_.erase(timer_it);
                timer_heap_.pop();
            }
        }
        return {false, Clock_tp{}};
    }
    
    void process_timers()
    {
        unique_lock<mutex> l(mutex_);
        while (timer_heap_.size() && timer_heap_.top().end_ <= Clock::now()) {
            auto timer_it = timer_heap_.top().timer_it_;
            auto timer = *timer_it;
            // remove from all structures
            auto hash_it = timer_id_hash_.find(timer_it->id_);
            if (hash_it != timer_id_hash_.end())
                timer_id_hash_.erase(hash_it);
            timers_.erase(timer_it);
            timer_heap_.pop();
            l.unlock();
            if (!timer.cancelled_)
                timer.handler_();
            l.lock();
        }
    }
    
    Timer_id generate_unique_id() { return unique_timer_id_++; }

private:
    struct Timer
    {
        Timer(Timeout_handler th, uint64_t id, int64_t period):
            handler_(move(th)), id_(id), period_(period)
        {}
        
        void cancel() { cancelled_ = true; }
        
        Timeout_handler handler_;
        uint64_t id_ = 0;
        int64_t period_ = 0;
        bool cancelled_ = false;
    };
    using Timer_list = list<Timer>;
    using Timer_list_it = Timer_list::iterator;

    struct Timer_slot
    {
        Timer_slot(const Clock_tp& end, const Timer_list_it& it):
            end_(end), timer_it_(it)
        {}
        Clock_tp end_;
        Timer_list_it timer_it_;
        bool operator>(const Timer_slot& r) const { return end_ > r.end_; }
    };
    
    Timer_list timers_;
    priority_queue<Timer_slot, vector<Timer_slot>, greater<Timer_slot>> timer_heap_;
    unordered_map<uint64_t, Timer_list_it> timer_id_hash_;
    
    Semaphore timers_sem_;
    bool done_ = false;
    uint64_t unique_timer_id_ = 0;
    mutable mutex mutex_;
};

int main()
{
    {
#if 0        
        Timer_queue tq;
        //tq.run();
        auto tid1 = tq.schedule_timer([](){}, 1);
        auto tid2 = tq.schedule_timer([](){}, 1);
        auto tid3 = tq.schedule_timer([](){}, 1);
        cout << "timer id: " << tid1 << endl;
        cout << "timer id: " << tid2 << endl;
        cout << "timer id: " << tid3 << endl;
        tq.cancel_timer(tid1);
        tq.cancel_timer(tid2);
        tq.cancel_timer(tid3);
        tq.cancel_timer(10);
#endif
    }
    
    {
         using namespace std::chrono_literals;
        Timer_queue tq;
        thread t([&tq]{ tq.run(); });
        
        auto start3 = Timer_queue::Clock::now();
        tq.schedule_timer([&start3]{ auto now = Timer_queue::Clock::now(); 
                                    std::chrono::duration<double, std::milli> elapsed = now-start3;
                                    cout << "[timeout]: well done! elapsed: " << elapsed.count() << endl; }, 
                                    50);
        auto start = Timer_queue::Clock::now();
        tq.schedule_timer([&start]{ auto now = Timer_queue::Clock::now(); 
                                    std::chrono::duration<double, std::milli> elapsed = now-start;
                                    cout << "[timeout]: well done! elapsed: " << elapsed.count() << endl; }, 
                                    1000);
        auto start1 = Timer_queue::Clock::now();
        tq.schedule_timer([&start1]{ auto now = Timer_queue::Clock::now(); 
                                    std::chrono::duration<double, std::milli> elapsed = now-start1;
                                    cout << "[timeout]: well done! elapsed: " << elapsed.count() << endl; }, 
                                    100);
/*        auto start2 = Timer_queue::Clock::now();
        tq.schedule_timer([&start2]{ auto now = Timer_queue::Clock::now(); 
                                    std::chrono::duration<double, std::milli> elapsed = now-start2;
                                    cout << "[timeout]: well done! elapsed: " << elapsed.count() << endl; }, 
                                    20);*/
        
        this_thread::sleep_for(60s);
        
        tq.stop();
        
        t.join();
    }

    return 0;
}
