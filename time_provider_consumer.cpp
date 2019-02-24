/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
#include <boost/signals2/signal.hpp>
using namespace std;

namespace Util
{
    string time_to_string(const chrono::system_clock::time_point& tp)
    {
        time_t t = chrono::system_clock::to_time_t(tp);
        string ts = ctime(&t);
        ts.resize(ts.size()-1);
        return ts;
    }
}

class Time_provider
{
public:
    using Slot_signature = void(const string& time_frmt);
    using Signal_type = boost::signals2::signal<Slot_signature>;
    using Clock_type = chrono::system_clock;
    using Timestamp_type =  chrono::system_clock::time_point;
    using Duration_type = chrono::duration<double, milli>;
    
    Time_provider()
    {}
    
    void start()
    {
        thread_ = thread([this](){ svc(); });
    }
    
    void wait()
    {
        if (thread_.joinable())
            thread_.join();
    }
    
    Signal_type& signal() { return signal_; }
    const Signal_type& signal() const { return signal_; }
    
protected:
    void svc()
    {
        while(1) {
            this_thread::sleep_for(5s);
            this->on_timeout();
        }
    }
    
    void on_timeout()
    {
        auto now = Clock_type::now();
//        Duration_type elapsed = chrono::duration_cast<Duration_type>(now-last_timestamp_);
//        cout << "[on_timeout]: done, elapsed: " << elapsed.count() << "ms\n";
        last_timestamp_ = now;
        string ts = Util::time_to_string(now);
        signal_(ts);
    }
    
private:
    Signal_type signal_;
    thread thread_;
    Timestamp_type last_timestamp_;
};

class Time_consumer1
{
public:
    Time_consumer1()
    {}
    
    void process(const string& ts)
    {
        cout << "[Time_consumer1]: " << ts << " its too late...\n";
    }
    
    void register_slot(Time_provider& provider)
    {
        provider.signal().connect([this](const string& s){ process(s); });
    }
    
private:
};

class Time_consumer2
{
public:
    Time_consumer2()
    {}
    
    void process(const string& ts)
    {
        cout << "[Time_consumer2]: " << ts << " never say never...\n";
    }
    
    void register_slot(Time_provider& provider)
    {
        provider.signal().connect([this](const string& s){ process(s); });
    }
    
private:
};

int main()
{
    Time_provider provider;
    Time_consumer1 consumer1;
    Time_consumer2 consumer2;
    
    consumer1.register_slot(provider);
    consumer2.register_slot(provider);
    
    provider.start();
    
    provider.wait();
    
    return 0;
}
