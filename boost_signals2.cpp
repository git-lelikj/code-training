#include <bits/stdc++.h>
#include <boost/signals2/signal.hpp>
using namespace std;

using Signal = boost::signals2::signal<void ()>;

//[ hello_world_def_code_snippet
struct HelloWorld
{
  void operator()() const
  {
    std::cout << "Hello, World!" << std::endl;
  }
};
//]

struct A
{
    A(int id=0):
        id_(id)
    {}

    void f() const { cout << "[A::f]: Hello from A id: " << id_ << endl; }
    
    void connect_to_signal(Signal& sig) const { sig.connect([this](){ f(); }); }
    
    int id_ = 0;
};

int main()
{
//[ hello_world_single_code_snippet
  // Signal with no arguments and a void return value
  Signal sig;

  // Connect a HelloWorld slot
  HelloWorld hello;
  sig.connect(hello);
  
  auto lmbd = [](){ cout << "Hello from lambda slot!\n"; };
  sig.connect(lmbd);
  
  A a1(55);
  sig.connect([a1](){ a1.f(); });
  a1.id_ = 66;

  A a2(55);
  sig.connect([&a2](){ a2.f(); });
  a2.id_ = 66;
  
  A a3(77);
  a3.connect_to_signal(sig);
  a3.id_ = 88;

  // Call all of the slots
  sig();
//]

  return 0;
}
