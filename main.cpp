#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <string>
#include <cassert>
#include "public.h"
#include "singleton.h"
#include "class_factory.h"
#include "active_object.h"
using namespace std;

namespace Common
{
    template<typename T, typename Base>
    shared_ptr<Base> create_singleton()
    {
        return dynamic_pointer_cast<Base>(T::get_instance());
    }
}

namespace Cls_factory_test
{
    using namespace Common;

//    enum CLSID_type {
//        CLSID_Class1 = 0,
//        CLSID_Class2
//    };

//    class ICommon
//    {
//    public:
//        virtual ~ICommon() {}
//    };

    class IInterface1: virtual public ICommon
    {
    public:
        virtual void f1() = 0;
    };

    class IInterface2: virtual public ICommon
    {
    public:
        virtual void f2() = 0;
    };

    class IInterface3: virtual public ICommon
    {
    public:
        virtual void f3() = 0;
    };

    class Class1: public IInterface1
    {
    public:
        void f1() { cout << "[Class1::f1]\n"; }
        ~Class1() { cout << "[Class1::~Class1]\n"; }
    };

    class Class2:   public IInterface2,
                    public IInterface3
    {
    public:
        void f2() { cout << "[Class2::f2]\n"; }
        void f3() { cout << "[Class2::f3]\n"; }
        ~Class2() { cout << "[Class2::~Class2]\n"; }
    };

    using Class_factory = Factory<CLSID_type, ICommon, std::function<std::shared_ptr<ICommon>(void)>>;
}

namespace Singleton_test
{
    using namespace Common;

    class IInterface: virtual public ICommon
    {
    public:
        virtual void f1() = 0;
    };

    class Class:    public Common::Shared_singleton<Class>,
                    public IInterface
    {
    public:
        ~Class() { cout << "[Class::~Class]\n"; }
        void f1() { cout << "[Class:f1]\n"; }
    private:
        Class() {}
        friend class Common::Shared_singleton<Class>;
    };
}

namespace AO_test
{
    using namespace Common;
    using Class_factory = Factory<CLSID_type, ICommon, std::function<std::shared_ptr<ICommon>(void)>>;

    class IInterface: public ICommon
    {
        virtual void fl1(int i, double d, string s) = 0;
    };

    class IControl: public ICommon
    {
        virtual void init() = 0;
    };

    class Proxy:    public IInterface
    {
    public:
        void init()
        {
            impl_ = Class_factory::get_instance()->create_object<IInterface>(CLSID_Class1);
        }

        void f1(int i, double d, string s)
        {
            assert(impl_!=nullptr);
            impl_->
        }

    private:
        shared_ptr<IInterface> impl_;
    };

    class Active:   public Active_object,
                    public IControl,
                    public IInterface
    {
    public:
        void init()
        {
            this->start();
        }

        void f1(int i, double d, string s)
        {
            cout << "[Active::f1]: i: " << i << ", d: " << d << ", s: " << s << endl;
        }
    };
}

int main(int argc, char *argv[])
{
    using namespace Common;
    using namespace Cls_factory_test;
    using namespace Singleton_test;
    using namespace AO_test;
#if 0
    cout << "[main]: class factory test =============================================\n";
    {
        Class_factory factory;

        cout << (factory.register_class(CLSID_Class1, &create_shared<Class1, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");
        cout << (factory.register_class(CLSID_Class2, &create_shared<Class2, ICommon>) == false?"[main]: failed to register CLSID_Class2\n":"[main]: registered CLSID_Class2\n");
    //    cout << (factory.register_class(CLSID_Class1, &create_shared<Class1, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");
        {
            std::shared_ptr<IInterface1> c = factory.create_object<IInterface1>(CLSID_Class1);
            if (c) {
                cout << "[main]: calling Class1::f1...\n";
                c->f1();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class1::IInterface1\n";
        }
        {
            std::shared_ptr<IInterface2> c = factory.create_object<IInterface2>(CLSID_Class1);
            if (c) {
                cout << "[main]: calling Class1::f2...\n";
                c->f2();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class1::IInterface2\n";
        }
        {
            std::shared_ptr<IInterface2> i2 = factory.create_object<IInterface2>(CLSID_Class2);
            if (i2) {
                cout << "[main]: calling Class2::f2...\n";
                i2->f2();
                cout << "[main]: ptr use_count: " << i2.use_count() << endl;
                cout << "[main]: query Class2::IInterface3...\n";
                shared_ptr<IInterface3> i3 = query_interface<IInterface3>(i2);
                if (i3) {
                    cout << "[main]: calling Class2::f3...\n";
                    i3->f3();
                    cout << "[main]: ptr i2 use_count: " << i2.use_count() << endl;
                    cout << "[main]: ptr i3 use_count: " << i3.use_count() << endl;
                }
                else
                    cout << "[main]: cant query Class2::IInterface3\n";
            }
            else
                cout << "[main]: cant create pointer to interface: Class2::IInterface2\n";
        }
        {
            std::shared_ptr<IInterface3> c = factory.create_object<IInterface3>(CLSID_Class2);
            if (c) {
                cout << "[main]: calling Class2::f3...\n";
                c->f3();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class2::IInterface3\n";
        }

        {
            shared_ptr<IInterface1> i1 = factory.create_object<IInterface1>(CLSID_Class1);
            shared_ptr<IInterface2> i2 = factory.create_object<IInterface2>(CLSID_Class2);
            shared_ptr<IInterface3> i3 = query_interface<IInterface3>(i2);
        }
    }
    cout << "[main]: singleton test =============================================\n";
    {
//        Class* c = new Class;
        shared_ptr<Class> s1 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << endl;
        shared_ptr<Class> s2 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }

    cout << "[main]: proceeding...\n";
    {
        shared_ptr<Class> s1 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << endl;
        shared_ptr<Class> s2 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }

    cout << "[main]: singleton + factory test =============================================\n";
    {
        Class_factory factory;

        cout << (factory.register_class(CLSID_Class1, &create_singleton<Class, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");

        {
            shared_ptr<IInterface> i1 = factory.create_object<IInterface>(CLSID_Class1);
            cout << "[main]: i1 use_count: " << i1.use_count() << ", calling f1...\n";
            i1->f1();
            shared_ptr<IInterface> i2 = factory.create_object<IInterface>(CLSID_Class1);
            cout << "[main]: i2 use_count: " << i2.use_count() << ", calling f1...\n";
            i2->f1();
        }
    }
#endif
#if 0
    cout << "[main]: active object test =============================================\n";
    {
        cout << "[main]: start AO test, main thread id: " << this_thread::get_id() << endl;
        Active_object ao;
        ao.start();
        this_thread::sleep_for(chrono::seconds(5));
        ao.send([](){ cout << "[mr]: called\n"; });
        this_thread::sleep_for(chrono::seconds(10));
        ao.stop();
        ao.wait();
    }
#endif
    cout << "[main]: active object test =============================================\n";
    {
        auto factory = Class_factory::get_instance();
    }
    cout << "[main]: end\n";
    return 0;
}
