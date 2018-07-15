#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <memory>
#include <functional>
using namespace std;

namespace Common
{

// Note: this implementation based on weak_ptr instance is correct:
//  The member instance_ use_count is 0 because it is weak_ptr, thus signleton is correctly deleted when instances are expred,
//  and not at the end of program
template <typename T>
class Shared_singleton
{
public:
    static shared_ptr<T> get_instance()
    {
        // return copy of shared_ptr (increment refcount)
        shared_ptr<T> shptr = instance_.lock();
        if (!shptr) {
            // if expred create new object
            // dont use make_shared because T constructor would be private
            shptr = shared_ptr<T>(new T);
            // store converted to weak_ptr
            instance_ = shptr;
            cout << "[Shared_singleton::get_instance]: create, use count: " << shptr.use_count() << endl;
        }
        cout << "[Shared_singleton::get_instance]: return, use count: " << shptr.use_count() << endl;
        return shptr;
    }

private:
    // use weak_ptr to have initial use_count at 0
    static weak_ptr<T> instance_;
};

template <typename T>
weak_ptr<T> Shared_singleton<T>::instance_;


// Note: this implementation based on shared_ptr instance is not correct:
//  The member instance_ use_count is 1, thus signleton is deleted only at the end of program,
//  and not when all instances are expired
#if 0
template <typename T>
class Shared_singleton
{
public:
    static shared_ptr<T> get_instance()
    {
        if (!instance_) {
            instance_ = shared_ptr<T>(new T);
            cout << "[Shared_singleton::get_instance]: create, use count: " << instance_.use_count() << endl;
        }
        cout << "[Shared_singleton::get_instance]: return, use count: " << instance_.use_count() << endl;
        return instance_;
    }

private:
    static shared_ptr<T> instance_;
};

template <typename T>
shared_ptr<T> Shared_singleton<T>::instance_;
#endif

}

#endif // SINGLETON_H
